// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

Quadtree::Quadtree() 
{

    root = NULL;


}

Quadtree::Quadtree(const PNG & source, int resolution)
{

       root = NULL;

       buildTree(source,resolution);

}



Quadtree::Quadtree(Quadtree const & other)
{

       if(other.root!=NULL){
        root = new QuadtreeNode(NULL,NULL,NULL,NULL,(other.root)->res,RGBAPixel());
        copy(root,other.root);
        }
}	


Quadtree:: ~Quadtree()
{	
          deletetree(root);
}


RGBAPixel Quadtree::getPixel(int x,int y ) const
{
  if(root==NULL) 
            {  
            return RGBAPixel();
            }
            
  else if ((x-1)*(y-1)>=((root->res)*(root->res))) 
            {  
            return RGBAPixel();
            }          
   else if(x<0||y<0)
   {
             return RGBAPixel();  
   }         
   
   else 
   {
     return getPixel(root,x,y);
   }
  

}


RGBAPixel Quadtree::getPixel(QuadtreeNode * subroot,int x,int y ) const
{
 
  if(subroot->res==1) {
  
     return subroot->element;
  
    }
     else {
         if((x<((subroot->res)/2)) && (y<((subroot->res)/2)))
         {
            if(subroot->nwChild != NULL)
            {
            return getPixel(subroot->nwChild,x,y);
             }
            else {
             return subroot->element;
             }
            }
         else if((x>=((subroot->res)/2)) && (y<((subroot->res)/2)))
         {
            if(subroot->neChild != NULL)
            {         
            return getPixel(subroot->neChild,x-((subroot->res)/2),y);
            }
            else {
             return subroot->element;
             }
            }
         else if((x<(subroot->res/2)) && (y>=(subroot->res/2)))
         {
          if(subroot->swChild != NULL)
            {    
            return getPixel(subroot->swChild,x,y-((subroot->res)/2)); 
            } 
          else {
             return subroot->element;
             }
             }
                   
         else if((x>=((subroot->res)/2)) && (y>=(subroot->res/2)))
         {
          if(subroot->swChild != NULL)
            {      
            return getPixel(subroot->seChild,x-((subroot->res)/2),y-((subroot->res)/2));      
             }
          else {
             return subroot->element;
             }
             
             }          
             
             return RGBAPixel();   
    }
}



Quadtree const & Quadtree::operator=(Quadtree const & other)	
{

        if((this!=&other)&&(other.root!=NULL)) {
         deletetree(root);
         root = new QuadtreeNode(NULL,NULL,NULL,NULL,other.root->res,RGBAPixel());
         copy(root,other.root);
         }
         
         return (*this);
         
}
void Quadtree::copy(QuadtreeNode*& this_root,QuadtreeNode* other_root) 
{
        if(other_root == NULL) {
        
            this_root = NULL;

        }
       
         else if(other_root->res==1) {
         
           (this_root->element) = (other_root->element);

         }
         
         else {
         
            this_root->nwChild = new QuadtreeNode(NULL,NULL,NULL,NULL,other_root->res/2,RGBAPixel());
            this_root->neChild = new QuadtreeNode(NULL,NULL,NULL,NULL,other_root->res/2,RGBAPixel());
            this_root->swChild = new QuadtreeNode(NULL,NULL,NULL,NULL,other_root->res/2,RGBAPixel());
            this_root->seChild = new QuadtreeNode(NULL,NULL,NULL,NULL,other_root->res/2,RGBAPixel()); 
                         
          //orig
   
            this_root->element = other_root->element;
            copy(this_root->nwChild,other_root->nwChild);
            copy(this_root->neChild,other_root->neChild);
            copy(this_root->swChild,other_root->swChild);            
            copy(this_root->seChild,other_root->seChild);                        
                               
         }
}


void Quadtree::deletetree(QuadtreeNode *& subroot) {

     if(subroot!=NULL) {
     deletetree(subroot->nwChild);
     deletetree(subroot->neChild);
     deletetree(subroot->swChild);
     deletetree(subroot->seChild); 
     delete subroot;
     subroot = NULL;
     }         
}


void Quadtree::buildTree(PNG const & source, int resolution)
{
     deletetree(root);
     root = new QuadtreeNode();
     root->res = resolution;  //ori
     buildTree(source,resolution,root,0,0);


}

void Quadtree::buildTree(PNG const & source, int resolution, QuadtreeNode *& subroot,int x, int y) {

       if(resolution==1) {
  
            subroot->res = resolution;       //ori
           
            subroot->element = *source(x,y);
       
       }
       
       else  {
       
       subroot->nwChild = new QuadtreeNode(NULL,NULL,NULL,NULL,subroot->res/2,RGBAPixel());
       subroot->neChild = new QuadtreeNode(NULL,NULL,NULL,NULL,subroot->res/2,RGBAPixel());
       subroot->swChild = new QuadtreeNode(NULL,NULL,NULL,NULL,subroot->res/2,RGBAPixel());
       subroot->seChild = new QuadtreeNode(NULL,NULL,NULL,NULL,subroot->res/2,RGBAPixel());                     
 
       
      
                  
       buildTree(source,subroot->res/2,subroot->nwChild,x,y);
       buildTree(source,subroot->res/2,subroot->neChild,x+(subroot->res/2),y);       
       buildTree(source,subroot->res/2,subroot->swChild,x,y+(subroot->res/2));       
       buildTree(source,subroot->res/2,subroot->seChild,x+(subroot->res/2),y+(subroot->res/2));       

                subroot->element.red = (subroot->nwChild->element.red+subroot->neChild->element.red+subroot->swChild->element.red+subroot->seChild->element.red)/4;
		subroot->element.green = (subroot->nwChild->element.green+subroot->neChild->element.green+subroot->swChild->element.green+subroot->seChild->element.green)/4;
		subroot->element.blue = (subroot->nwChild->element.blue+subroot->neChild->element.blue+subroot->swChild->element.blue+subroot->seChild->element.blue)/4;


              
       }
       

}

PNG Quadtree::decompress()const
{
	if(root == NULL)
		return PNG();
	PNG newone(root->res,root-> res);
   for (int j =0;j<root->res;j++){  
      for(int i = 0;i<root->res;i++){
      
         *newone(i,j) = getPixel(i,j);
       
      }
      
      }
	return newone;	
}

int Quadtree::pruneSize(int tolerance)const
{
    return pruneSize(tolerance,root);
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode* subroot) const
{
  if(subroot!=NULL) {

   bool nw;
   bool ne;
   bool sw;
   bool se;
   
   nw = valid(subroot,tolerance,subroot->nwChild);
   ne = valid(subroot,tolerance,subroot->neChild);  
   sw = valid(subroot,tolerance,subroot->swChild);
   se = valid(subroot,tolerance,subroot->seChild);  

   if (nw&&ne&&sw&&se) 
    {
    return 1;
    }
  
    else {
    
      return pruneSize(tolerance,subroot->nwChild)+pruneSize(tolerance,subroot->neChild)+pruneSize(tolerance,subroot->swChild)+pruneSize(tolerance,subroot->seChild);
    
    }  
  
}
 return 0;
}
void Quadtree::prune(int tolerance)
{

   prune(tolerance,root);

}

void Quadtree::prune(int tolerance, QuadtreeNode* & subroot)
{
  if(subroot!=NULL) {

     if(valid(subroot,tolerance,subroot->nwChild) && valid(subroot,tolerance,subroot->neChild)&& valid(subroot,tolerance,subroot->swChild)&& valid(subroot,tolerance,subroot->seChild)) {
        deletetree(subroot->nwChild);
        deletetree(subroot->neChild);
        deletetree(subroot->swChild);             
        deletetree(subroot->seChild);     
      }

      else { 
         prune(tolerance,subroot->nwChild);
         prune(tolerance,subroot->neChild); 
         prune(tolerance,subroot->swChild); 
         prune(tolerance,subroot->seChild);                
      }
   }
}

bool Quadtree::valid(QuadtreeNode * &subroot,int tolerance,QuadtreeNode * &leaf) const
{
 
     if(leaf==NULL)
     
     {  return true; }
  else {

      RGBAPixel ln = leaf->element;
      RGBAPixel rn = subroot->element;
      
  
     if(leaf->nwChild==NULL) 
     {

      if((rn.red-ln.red)*(rn.red-ln.red)+(rn.green-ln.green)*(rn.green-ln.green)+(rn.blue-ln.blue)*(rn.blue-ln.blue)<=tolerance){      
         return true;        
       }     
 
      else {      
        return false;      
      }
 
    }
    
    else {    
    return valid(subroot,tolerance,leaf->nwChild) && valid(subroot,tolerance,leaf->neChild) && valid(subroot,tolerance,leaf->swChild) && valid(subroot,tolerance,leaf->seChild);
    }
    
    }

}


int Quadtree::idealPrune(int numLeaves)const
{

  int max = 3*255*255;
  int min = 0;
  
  return idealPrune(numLeaves,min,max);
}

int Quadtree::idealPrune(int numLeaves,int min, int max)const
{
  int tolerance = (min+max)/2;
  if(tolerance == max || tolerance == min ) {
  
    if(pruneSize(tolerance)>numLeaves)
     {  return max; }
    else
     { return min; } 
     
  
  }
  else if(pruneSize(tolerance)>numLeaves) {
  
     return idealPrune(numLeaves,tolerance,max);
   
  }
  
  else  {
  
     return idealPrune(numLeaves,min,tolerance);  
  
  }
}
void Quadtree::clockwiseRotate()
{
    clockwiseRotate(root);
}	

void Quadtree::clockwiseRotate(QuadtreeNode*& subroot)
{ 
   if(subroot==NULL) {

      return;
     
     }     
   if(subroot->res==1)
   {
     return;
   }  
     
   else {
   
      QuadtreeNode* temp1;
      QuadtreeNode* temp2; 
      QuadtreeNode* temp3;     

      temp1 = subroot->neChild;
      subroot->neChild = subroot->nwChild;     
      temp2 = subroot->seChild;
      subroot->seChild = temp1;
      temp3 = subroot->swChild;   
      subroot->swChild = temp2;
      subroot->nwChild = temp3;
      
      temp1 = NULL;
      temp2 = NULL;
      temp3 = NULL;

      clockwiseRotate(subroot->nwChild); 
      clockwiseRotate(subroot->neChild);      
      clockwiseRotate(subroot->swChild);      
      clockwiseRotate(subroot->seChild);                             
            
   }
 


}









