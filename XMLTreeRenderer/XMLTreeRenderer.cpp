// XMLTreeRenderer.cpp : 定义 DLL 应用程序的入口点。
//

//sibling延展的方向称为sibling direction, sibdir
//parent延展的方向称为parent direction, pardir
#include "stdafx.h"

#include "LayoutTree.h"
#include "TextLayoutTreeNode.h"

#define TIXML_USE_STL
#include <tinyxml.h>
#include "inc_gdiplus.h"

#include <eflib/include/eflib.h>
#include <boost/python.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace Gdiplus;

class GDIPlusInitializer
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
public:
	GDIPlusInitializer(){
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	~GDIPlusInitializer(){
		GdiplusShutdown(gdiplusToken);
	}
};

void ParseElemToLayoutNodeRecursive(
									TiXmlElement* elem,
									TextLayoutTreeNode* parent_node,
									LayoutTree* owner,
									Font* font,
									Graphics* g,
									int width,
									StringFormat* strfmt
									)
{
	std::string elem_str;
	elem_str += elem->Attribute("name");
	elem_str += "\n(";
	elem_str += elem->Attribute("global_weight");
	elem_str += ")";

	TextLayoutTreeNode* cur_node = owner->create_node<TextLayoutTreeNode>(parent_node);
	cur_node->set_renderer_params(font, width, g, elem_str, strfmt);

	for(TiXmlElement* child = elem->FirstChildElement("feature"); child != NULL; child = child->NextSiblingElement("feature"))
	{
		ParseElemToLayoutNodeRecursive(child, cur_node, owner, font, g, width, strfmt);
	}
	
}

void ParseDomToLayoutTree(const std::string& xmlFile,
						  LayoutTree* tree,
						  Font* font,
						  Graphics* g,
						  int width,
						  StringFormat* strfmt)
{
	TiXmlDocument doc;
	doc.LoadFile(xmlFile);
	ParseElemToLayoutNodeRecursive(doc.FirstChildElement("feature"), NULL, tree, font, g, width, strfmt);
}

void RenderXMLTree(const std::string& xmlFile, const std::string& outputFile){
	//进行初始化
	static GDIPlusInitializer __init_gdiplus;

	//设置树的公共要素
	LayoutTree tree;
	tree.padding(10.0f);
	tree.pardir_spacer(20.0f);
	tree.sibdir_spacer(20.0f);

	//预构造绘制元素
	Bitmap* bmp = new Bitmap(1, 1, PixelFormat32bppARGB);
	Graphics* g = Graphics::FromImage(bmp);
	g->SetSmoothingMode(SmoothingModeAntiAlias);

	Font font(L"宋体", 24);
	StringFormat strfmt;
	strfmt.SetAlignment(StringAlignmentCenter);
	strfmt.SetLineAlignment(StringAlignmentCenter);

	//填充树节点，并计算布局
	ParseDomToLayoutTree(xmlFile, &tree, &font, g, 10, &strfmt);
	tree.root()->calculate_size_recursive();
	tree.root()->update_layout();

	//构造输出位图
	delete bmp;
	bmp = new Bitmap(tree.width(), tree.height(), PixelFormat32bppARGB);
	delete g;
	g = Graphics::FromImage(bmp);
	g->SetSmoothingMode(SmoothingModeHighQuality);

	//重新构造树节点并在输出位图上进行绘制
	tree.clear();
	ParseDomToLayoutTree(xmlFile, &tree, &font, g, 10, &strfmt);
	tree.root()->calculate_size_recursive();
	tree.root()->update_layout();
	tree.root()->render();

	//保存位图
	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	bmp->Save(to_wide_string(outputFile).c_str(), &pngClsid, NULL);

	delete bmp;
	delete g;
}

BOOST_PYTHON_MODULE(XMLTreeRenderer)
{
	using namespace boost::python;
	def("RenderXMLTree", RenderXMLTree);
}