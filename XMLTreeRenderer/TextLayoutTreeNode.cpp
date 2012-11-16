#include "TextLayoutTreeNode.h"
#include "LayoutTree.h"
#include <eflib/include/stl_utilities.h>

#include <boost/foreach.hpp>

using namespace Gdiplus;
using namespace std;

void TextLayoutTreeNode::calculate_size()
{
	SizeF extent_size;
	graphics_->MeasureString(text_.c_str(), -1, font_, PointF(extent_.X, extent_.Y), strfmt_, &extent_);
	
	extent_.Width += owner_->padding() * 2.0f;
	extent_.Height += owner_->padding() * 2.0f;
}

void TextLayoutTreeNode::calculate_size_recursive()
{
	calculate_size();
	BOOST_FOREACH (LayoutTreeNode* child, children_)
	{
		child->calculate_size_recursive();
	}
}

void TextLayoutTreeNode::set_renderer_params( Font* font, int width, Graphics* g, const string& text, StringFormat* strfmt)
{
	font_ = font;
	max_width_ = width;
	graphics_ = g;
	text_ = to_wide_string(text);
	strfmt_ = strfmt;
}

void TextLayoutTreeNode::render()
{
	Pen* pen = new Pen(Color::Black, 2.0);
	Brush* text_brush = new SolidBrush(Color::Black);

	graphics_->DrawRectangle(pen, Round(extent_));
	graphics_->DrawString(text_.c_str(), -1, font_, extent_, strfmt_, text_brush);

	BOOST_FOREACH (LayoutTreeNode* child, children_)
	{
		//»æÖÆÐ±Ïß
		float childSibDirPos = (child->extent().GetTop() + child->extent().GetBottom()) / 2.0f;
		float childParDirPos = child->extent().GetLeft();

		float curSibDirPos = (extent_.GetTop() + extent_.GetBottom()) / 2.0f;
		float curParDirPos = extent_.GetRight();

		graphics_->DrawLine(pen, PointF(childParDirPos, childSibDirPos), PointF(curParDirPos, curSibDirPos));

		child->render();
	}
}

TextLayoutTreeNode::TextLayoutTreeNode( LayoutTreeNode* parent, LayoutTree* owner)
	:LayoutTreeNode(parent, owner),
	font_(NULL),
	max_width_(0),
	graphics_(NULL),
	text_(L""),
	strfmt_(NULL)
{
}

TextLayoutTreeNode::~TextLayoutTreeNode()
{
}