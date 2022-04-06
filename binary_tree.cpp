#include <iostream>

	
	struct node {
		
		public:
			int				value;
			node			*left;
			node			*right;
			node			*parent;
		public:
			node() : value(0), left(NULL), right(NULL), parent(NULL) {}
			node(int &val) : value(val), left(NULL), right(NULL), parent(NULL) {}
			node& operator=(const node& other) {
				if(this != &other) {
					value = other.value;
					left = other.left;
					right = other.right;
					parent = other.parent;
				}
				return *this;
			}

	};


	bool search(node *root, int val) {
		if (root == NULL)
			return false;
		if (val < root->value)
			search(root->left, val);
		else if (val > root->value)
			search(root->right, val);
		else if (root->value == val)
			return true;
	}

	node *search_val(node *root, int val) {
		if (root == NULL)
			return NULL;
		if (val < root->value)
			search(root->left, val);
		else if (val > root->value)
			search(root->right, val);
		else if (root->value == val)
			return root;
	}

	// void insert(node *root, int val) {
	// 	if (root == NULL) {
	// 		root->value = val;
	// 		root->left = NULL;
	// 		root->right = NULL;
	// 	}
	// 	if (val < root->value)
	// 		insert(root->left, val);
	// 	else if (val > root->value)
	// 		insert(root->right, val);
	// 	else if (val == root->value)
	// 		insert(root->right, val);				
	// }

	// node *insert(node *new_node) {
	// 	if (root == header)
	// 		root = new_node;
	// 	else
	// 		_insert_to_node(_root, new_node);
	// 	return new_node;	
	// }

	bool isEmpty( node *root )
	{
		return root == NULL;
	}

	int size( node *tree )
	{
		if ( !isEmpty( tree ))
			return 1 + size( tree->left ) + size( tree->right );
		else return 0;
	}

	node *insert_to_node(node *root, node *new_node) {
		if (new_node->value == root->value){
			if (root->left != NULL)
				return (insert_to_node(root->left, new_node));
			root->left = new_node;
		}
		else{
			if (root->right != NULL)
				return (insert_to_node(root->right, new_node));
			root->right = new_node;
		}
		new_node->parent = root;
		return (new_node);
	}

	void print(node *root) {
		if (root == NULL)
			return;
		print(root->left);
		std::cout << root->value << std::endl;
		print(root->right);
	}

	node *max_node(node *root) {
		if (root->right == NULL)
			return root;
		else
			return max_node(root->right);
	}

	node *min_node(node *root) {
		if (root->left == NULL)
			return root;
		else
			return min_node(root->left);
	}


	// void insert (node *root, node *n) {
	// 	node *temp = new node();
	// 	node *y = NULL;

	// 	while (temp != NULL) {
	// 		y = temp;
	// 		if (n->value < temp->value)
	// 			{temp = temp->left; }
	// 		else
	// 			{temp = temp->right; }
	// 	}
	// 	n->parent = y;
	// 	if (y == NULL)
	// 		temp = n;
	// 	else if (n->value < y->value)
	// 		y->left = n;
	// 	else
	// 		y->right = n;
	// }

	void insert( node *&root, node *new_node )
	{
		if ( isEmpty( root ))
			root = new_node;

		else
		{
			if ( new_node->value < root->value )
				insert( root->left, new_node );

			else insert( root->right, new_node );
		}
	
	}

	// void insert(node *root, node *new_node) {
		
	// 	if (root->left == NULL && new_node->value < root->value)
	// 		root->left = new_node;
	// 	else if (root->right == NULL && new_node->value > root->value)
	// 		root->right = new_node;
	// 	else {
	// 		node *tmp = root;
	// 		while (tmp != NULL)
	// 			if(tmp->value < new_node->value)
	// 				tmp = tmp->left;
	// 			else
	// 				tmp = tmp->right;
	// 		if (tmp->left == NULL)
	// 			tmp->left = new_node;
	// 		else
	// 			tmp->right = new_node;
	// 	}
	// }

// 	void insert(node *root, node *new_node) {
// 		node *temp = root;
// 		node *insert_after = NULL;
// 		while (temp != NULL)
// 			insert_after = temp;
// 			if (new_node->value < temp->value)
// 				temp = temp->left;
// 			else
// 				temp = temp->right;
// 		new_node->parent = insert_after;
// 		if (insert_after == NULL)
// 			root = new_node;
// 		else if (new_node->value < insert_after->value)
// 			insert_after->left = new_node;
// 		else
// 			insert_after->right = new_node;
// }

// void insert(node *root, node *new_node) {
// 	node *temp = NULL;
// 	while (root != NULL)
// 		temp = root;
// 		if (new_node->value < root->value)
// 			root = root->left;
// 		else
// 			root = root->right;
// 	new_node->parent = temp;
// 	if (temp == NULL)
// 		root = new_node;
// 	else if (new_node->value < temp->value)
// 		temp->left = new_node;
// 	else
// 		temp->right = new_node;
// }

int main () {
	node *tree = new node();
	tree->value = 12;
	node left_node = node();
	left_node.value = 10;	
	node right_node = node();
	right_node.value = 14;
	node left_node2 = node();
	left_node2.value = 8;	
	node right_node2 = node();
	right_node2.value = 21;
	// for(int i = 0; i < 10; ++i)
	// insert(tree, &left_node);
	// insert(tree, &right_node);

	insert(tree, &left_node);
	insert(tree, &right_node);
	insert(tree, &left_node2);
	insert(tree, &right_node2);

	// insert(tree, &left_node2);
	// insert(tree, &right_node2);
	// tree.right->value = 1;
	
	// tree->left->value = 1;
	// std::cout << search_val(tree, 12)->value << "\n";
	print(tree);
	// std::cout << tree->left << std::endl;
	// std::cout << tree->right-> << std::endl;
	// print(tree->left);
	// print(tree->right);
	std::cout << "size = " << size(tree) << "\n";
	



}