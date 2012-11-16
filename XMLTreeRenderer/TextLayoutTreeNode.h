#pragma once

#include "LayoutTreeNode.h"
#include "inc_gdiplus.h"

#include <string>

class TextLayoutTreeNode : public LayoutTreeNode
{
	friend class LayoutTree;

	int						max_width_;
	std::wstring			text_;
	Gdiplus::Font*			font_;
	Gdiplus::Graphics*		graphics_;
	Gdiplus::StringFormat*	strfmt_;

public:
	TextLayoutTreeNode(LayoutTreeNode* parent, LayoutTree* owner = NULL);
	~TextLayoutTreeNode();

	virtual void calculate_size();
	virtual void calculate_size_recursive();

	void set_renderer_params(
		Gdiplus::Font* font,
		int width,
		Gdiplus::Graphics* g,
		const std::string& text,
		Gdiplus::StringFormat* strfmt
		);

	void render();
};