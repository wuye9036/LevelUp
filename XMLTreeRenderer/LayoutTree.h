#pragma once

#include "LayerInfo.h"
#include "LayoutTreeNode.h"
#include <algorithm>

#undef max
#undef min

class LayoutTreeNode;

class LayoutTree
{
	LayoutTreeNode*	root_;
	LayerInfo*		info_;
	float			sibdir_spacer_;
	float			pardir_spacer_;
	float			padding_;

public:
	LayoutTree():info_(new LayerInfo()), root_(NULL), sibdir_spacer_(0.0f), pardir_spacer_(0.0f), padding_(0.0f){
	}

	~LayoutTree(){
		delete root_;
		delete info_;
	}

	void clear(){
		delete root_;
		root_ = NULL;
		info_->reset();
	}

	template <class T>
	T* create_node(LayoutTreeNode* parent)
	{
		if (parent == NULL){
			if (root_) {
				clear();
			}
			root_ =  new T(NULL, this);
			return (T*)root_;
		}

		if (parent->owner_ != this){
			return NULL;
		}

		return new T(parent);
	}

	float sibdir_spacer() const{
		return sibdir_spacer_;
	}
	void sibdir_spacer(float v){
		sibdir_spacer_ = v;
	}

	float pardir_spacer() const{
		return pardir_spacer_;
	}
	void pardir_spacer(float v){
		pardir_spacer_ = v;
	}

	float padding() const{
		return padding_;
	}

	void padding(float v){
		padding_ = v;
	}

	LayerInfo* layer_info(){
		return info_;
	}

	float width(){
		float ret_width = 0.0f;
		for(size_t lvl = 0; lvl < info_->count(); ++lvl)
		{
			ret_width += info_->pardir_min_distance(lvl);
			ret_width += pardir_spacer_;
		}
		return ret_width;
	}

	float height(){
		float ret_height = 0.0f;
		for(size_t lvl = 0; lvl < info_->count(); ++lvl){
			ret_height = std::max (info_->legal_sibdir_pos(lvl), ret_height);
		}
		return ret_height;
	}

	LayoutTreeNode* root()
	{
		return root_;
	}
};