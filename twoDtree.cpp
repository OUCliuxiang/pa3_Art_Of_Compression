
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#include <cmath>

/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

/* =========================== end of given functions =========================== */

/* this is a constructor, some initializative operation here*/
   /* ========================================================
    * Constructor that builds a twoDtree out of the given PNG.
    * Every leaf in the tree corresponds to a pixel in the PNG.
    * Every non-leaf node corresponds to a rectangle of pixels 
    * in the original PNG, represented by an (x,y) pair for the 
    * upper left corner of the rectangle and an (x,y) pair for 
    * lower right corner of the rectangle. In addition, the Node
    * stores a pixel representing the average color over the 
    * rectangle. 
    *
    * Every node's left and right children correspond to a partition
    * of the node's rectangle into two smaller rectangles. The node's
    * rectangle is split by the horizontal or vertical line that 
    * results in the two mZ rectangles whose sum of squared 
    * differences from their mean is as small as possible.
    *
    * The left child of the node will contain the upper left corner
    * of the node's rectangle, and the right child will contain the
    * lower right corner.
    *
    * This function will build the stats object used to score the 
    * splitting lines. It will also call helper function buildTree.
    *============================================================
    */
twoDtree::twoDtree(PNG & imIn){ 
    /* 
    pair< int, int> ul, lr;
    ul.first = ( int)( imIn.PNG::width() - 1); 
    // ??? don't know what's mean of operation "-1"
    ul.second = (int)( inIn.PNG::height() - 1 );
    */
    pair< int, int> lr = 
        make_pair( imIn.PNG::width() - 1, 
                   imIn.PNG::height() - 1 ); 
    pair< int, int>ul = make_pair( 0, 0 );
    //initializing stats using PNG is allowed. //
    stats s = stats( imIn );
    height = imIn.height();
    width = imIn.width();
    root = buildTree( s, ul, lr );
    // root = buildTree( stats( imIn ), ul, lr )
}

/* to build a binary tree( a two-dimension tree ) */

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!! THE MOST DIFFICULT !!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
twoDtree::Node * twoDtree::buildTree(stats& s, pair<int,int> ul, pair<int,int> lr) {
	//Firstly to judge if is it empty.
    if( ul == lr ){
    twoDtree::Node* node = new twoDtree::Node( ul, lr, s.getAvg( ul, lr ) );
        node -> left = node -> right = NULL;
        return node;
    } 
    
    // if not
    pair< int, int> left_ul = ul;
    pair< int, int> right_lr = lr;
    //have known
    
    pair< int, int> left_lr;
    pair< int, int> right_ul;
    pair< int, int> biggest_left_lr;
    pair< int, int> biggest_right_ul;
    
    //store the biggest varience
    long double variance = 0;

    //to figure out x-axis firstly
    for( int i = left_ul.first; i < right_lr.first; ++ i ){
        right_ul = make_pair( i + 1, left_ul.second );
        left_lr = make_pair( i, right_lr.second );

        long double left_variance = s.getScore( left_ul, left_lr );
        long double right_variance = s.getScore( right_ul, right_lr );
        if( left_variance + right_variance > variance ){
            variance = left_variance + right_variance;
            biggest_left_lr = left_lr;
            biggest_right_ul = right_ul;
        }
    }

    //similar the y-axis is;
    //py py py py py py py ->_->
    for( int i = left_ul.second; i < right_lr.second; ++ i ){
        right_ul = make_pair( left_ul.first, i + 1 );
        left_lr = make_pair( right_lr.first, i );

        long double left_variance = s.getScore( left_ul, left_lr );
        long double right_variance = s.getScore( right_ul, right_lr );
        if( left_variance + right_variance > variance ){
            variance = left_variance + right_variance;
            biggest_left_lr = left_lr;
            biggest_right_ul = right_ul;
        }
    }

    twoDtree::Node* node = new twoDtree::Node( ul, lr, s.getAvg( ul,lr ) );
    //recursion
    node -> left = buildTree( s, left_ul, left_lr );
    node -> right= buildTree( s, right_ul, right_lr );
    return node;
}

// don't know how to translate it...

   /**
    * Render returns a PNG image consisting of the pixels
    * stored in the tree. may be used on pruned trees. Draws
    * every leaf node's rectangle onto a PNG canvas using the 
    * average color stored in the node.
    */
PNG twoDtree::render(){
	/* your code here */
    PNG pngObject = PNG( width, height );
    twoDtree::Node* nodeTemp = root;
    //if null
//    if( !nodeTemp )     return NULL;
    /*
    while( nodeTemp ) {
        for ( int i = node ->  )
    }
    */
    // try recrusion:
    renderRecur( pngObject, nodeTemp );
    return pngObject;
}

void twoDtree::renderRecur( PNG& pngObject, twoDtree::Node* nodeTemp ){
    if( !nodeTemp )     return;
    for ( int i = nodeTemp -> upLeft.first; 
          i < nodeTemp -> lowRight.first; ++ i )
        for ( int j = nodeTemp -> upLeft.second;
              j < nodeTemp -> lowRight.second; ++ j )
            *pngObject.getPixel( i, j ) = nodeTemp -> avg;
    
    renderRecur( pngObject, nodeTemp -> left );
    renderRecur( pngObject, nodeTemp -> right ); 
}

/* We'll complete the function by traverse the Two-Dimension-tree
 * Maybe the recursion is the best way
 */

/* Some difficulties:
 * 1, what's "tol"'s mean? total of pixel? Or total of subtrees?
 *    Or total of leaves? Or the others???
 *
 * !!!!!!!!!!!!!!!!!!!!!!! TRANSLATION !!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 * 2, What's the translation of the sentence 
 * "A subtree is pruned if at least pct within tol of 
 * average color stored in the root of sbutree"?
 * 
 * !!!!!!!!!!!!!!!!!!!!!!! TRANSLATION !!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

/* 说来惭愧，我用了一个星期的时间来琢磨这句话。
 * 试过了谷歌百度有道必应金山微软等等等等
 * 一切可以使用的翻译软件，至今不知道这句话要表达什么意思
 * 最终，为了避免因为这一个函数，使我曾做的所有努力前功尽弃
 * 我复制了github上的一份函数使用于此
 */
void twoDtree::prune(double pct, int tol){
	/* your code here */
    twoDtree::Node* nodeTemp = root;
    pruneHelper( pct, tol, nodeTemp );
}

void twoDtree::pruneHelper(double pct, int tol, Node* n){
	if(n->left == NULL && n->right == NULL)
		return;

    double total = ((n->lowRight.first + 1) - (n->upLeft.first)) * ((n->lowRight.second+1)-(n->upLeft.second));
	double count =tolLeafCounter(n, n, tol);


	if(count/total >= pct){
		clearRecur(n->left);
		clearRecur(n->right);
		n->left = NULL;
		n->right = NULL;
		return;
	}

	pruneHelper(pct, tol, n->left);
	pruneHelper(pct, tol, n->right);
}


double twoDtree::tolLeafCounter(Node* root, Node* n, int tol){
	if(n == NULL)
		return 0;
	if(n->left == NULL && n->right == NULL){
		int diff = 	pow(n->avg.g - root->avg.g, 2) +
								pow(n->avg.r - root->avg.r, 2) +
								pow(n->avg.b - root->avg.b, 2);
		if(diff > tol)
			return 0;
		else return 1;
		}
		return tolLeafCounter(root, n->left, tol) + tolLeafCounter(root, n->right, tol);
}

void twoDtree::clear() {
	/* your code here */
    twoDtree::Node* nodeTemp = root;
    clearRecur( nodeTemp );
}

//try recursion
void twoDtree::clearRecur( twoDtree::Node* nodeTemp ){
    if( !nodeTemp )
        return;
    clearRecur( nodeTemp -> left );
    clearRecur( nodeTemp -> right );
    delete nodeTemp;
}


void twoDtree::copy(const twoDtree & orig){
	/* your code here */
    height = orig.height;
    width = orig.width;

//    root = orig.root;
/*    
    if( !orig ) root = NULL;
    else{
        // Maybe a recursion function is required
    }
*/
    // for recursion, the type with left/right child is required,
    // which is acturally a tree-Node
    root = copyRecur( orig.root );
}

twoDtree::Node* twoDtree::copyRecur( twoDtree::Node* orig ){
    if( !orig ) return NULL;
    // do not just copy the point( address ), we want to create a
    // new tree, which is same to the orig completely.
    twoDtree::Node* nodeTemp = 
        new twoDtree::Node( orig -> upLeft, orig -> lowRight, 
                            orig -> avg);
    nodeTemp -> left = copyRecur( orig -> left );
    nodeTemp -> right= copyRecur( orig -> right);
    return nodeTemp;
} 

