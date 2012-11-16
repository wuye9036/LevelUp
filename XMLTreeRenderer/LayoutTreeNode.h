#pragma once

#include "inc_gdiplus.h"
#include <boost/utility.hpp>
#include <vector>

class LayoutTree;

class LayoutTreeNode : public boost::noncopyable
{
	friend class LayoutTree;

protected:
	LayoutTree*						owner_;
	LayoutTreeNode*					parent_;
	int								level_;
	Gdiplus::RectF					extent_;
	std::vector<LayoutTreeNode*>	children_;

	void layout_sibdir();
	void layout_pardir(float min_pos);

public:
	LayoutTreeNode( LayoutTreeNode* parent, LayoutTree* owner = NULL);
	virtual ~LayoutTreeNode();

	virtual void calculate_size() = 0;
	virtual void calculate_size_recursive() = 0;

	const std::vector<LayoutTreeNode*> children() const;
	std::vector<LayoutTreeNode*>& children();

	const Gdiplus::RectF& extent() const;
	Gdiplus::RectF& extent();

	void update_layout();
	virtual void render() = 0;
};