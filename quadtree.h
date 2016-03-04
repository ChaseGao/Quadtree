// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	
	Quadtree();
	Quadtree(const PNG & source, int resol);
	void buildTree(PNG const & source, int resol);
	~Quadtree();	
	Quadtree(Quadtree const & other);
        Quadtree const & operator=(Quadtree const & other);	
	RGBAPixel getPixel(int x, int y) const;
	PNG decompress()const;	
	int pruneSize(int tolerance)const;
	void prune(int tolerance);
	int idealPrune(int numLeaves)const;
	void clockwiseRotate();				
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child
                int res;
		RGBAPixel element;  // the pixel stored as this node's "data"
		QuadtreeNode():nwChild(NULL), neChild(NULL), swChild(NULL), seChild(NULL),res(0),element(RGBAPixel()){/*empty*/};
		QuadtreeNode(QuadtreeNode* Child0, QuadtreeNode* Child1, QuadtreeNode* Child2, QuadtreeNode* Child3, int resol, RGBAPixel a): nwChild(Child0), neChild(Child1), swChild(Child2), seChild(Child3), res(resol), element(a){/*empty*/};		
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	void buildTree(PNG const & source, int resolution, QuadtreeNode *& subroot,int x, int y);
	RGBAPixel getPixel(QuadtreeNode* subroot,int x,int y ) const;
        void deletetree(QuadtreeNode *& subroot);	
        void copy(QuadtreeNode*& this_root,QuadtreeNode* other_root);
        void decompress(PNG * & newone,int resolution,int x, int y) const;
	void clockwiseRotate(QuadtreeNode* & subroot);	
        bool valid(QuadtreeNode * &subroot,int tolerance,QuadtreeNode * &leaf) const; 
	void prune(int tolerance, QuadtreeNode* &subroot);	
	int pruneSize(int tolerance, QuadtreeNode* subroot) const;
	int idealPrune(int numLeaves,int min, int max)const;		        	        	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
