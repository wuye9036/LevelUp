#include "LayoutTreeNode.h"
#include "LayoutTree.h"

#include "boost/foreach.hpp"

using namespace std;

LayoutTreeNode::LayoutTreeNode( LayoutTreeNode* parent, LayoutTree* owner)
	:children_(0),
	parent_(parent),
	extent_(0.0f, 0.0f, 0.0f, 0.0f)
{
	if (parent == NULL){
		level_ = 0;
		owner_ = owner;
	} else {
		level_ = parent->level_ + 1;
		parent_->children_.push_back(this);
		owner_ = parent->owner_;
	}
}

LayoutTreeNode::~LayoutTreeNode(){
	BOOST_FOREACH (LayoutTreeNode* child, children_)
	{
		delete child;
	}
}

const std::vector<LayoutTreeNode*> LayoutTreeNode::children() const
{
	return children_;
}

std::vector<LayoutTreeNode*>& LayoutTreeNode::children()
{
	return children_;
}

const Gdiplus::RectF& LayoutTreeNode::extent() const
{
	return extent_;
}

Gdiplus::RectF& LayoutTreeNode::extent()
{
	return extent_;
}

void LayoutTreeNode::update_layout()
{
	layout_sibdir();
	layout_pardir(0.0f);
}

//parent - child 的方向为自左向右
void LayoutTreeNode::layout_sibdir()
{
	float originSibDirPos = owner_->layer_info()->legal_sibdir_pos(level_);
	extent_.Y = originSibDirPos;
	
	if (!children_.empty())
	{
		float childrenSibDirTotalLength(0.0f);
		for(vector<LayoutTreeNode*>::iterator it = children_.begin();
			it != children_.end();
			++it)
		{
			childrenSibDirTotalLength += (*it)->extent().Height;
		}
		childrenSibDirTotalLength += ((children_.size() - 1) * owner_->sibdir_spacer());
		float legalSibDirPos = originSibDirPos
			+ (extent_.Height / 2.0f) 
			- (childrenSibDirTotalLength / 2.0f);
		
		owner_->layer_info()->legal_sibdir_pos(level_+1, legalSibDirPos);

		for (size_t i_child = 0; i_child < children_.size(); ++i_child)
		{
			children_[i_child]->layout_sibdir();
		}

		float sibdir_center = 
			(
			children_[0]->extent().GetTop()
			+ children_[children_.size() - 1]->extent().GetBottom()
			) / 2.0F;

		extent().Y = sibdir_center - extent_.Height / 2.0F;
	}

	owner_->layer_info()->legal_sibdir_pos(
		level_,
		extent_.GetBottom() + owner_->sibdir_spacer()
		);

	owner_->layer_info()->pardir_min_distance(level_, extent_.Width);
}

void LayoutTreeNode::layout_pardir( float min_pos )
{
	extent_.X = min_pos;
	BOOST_FOREACH (LayoutTreeNode* child, children_)
	{
		child->layout_pardir(min_pos + owner_->layer_info()->pardir_min_distance(level_) + owner_->pardir_spacer());
	}
}