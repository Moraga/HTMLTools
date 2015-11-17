#include <string>
#include <vector>

struct Node {
	std::string nodeName;
	std::string nodeType;
	std::string nodeValue;
	Node* parentNode;
	std::vector<Node*> childNodes;
	static std::string end[];
	virtual ~Node();
	void appendChild(Node&);
};

struct AttributeNode: public Node {
	std::string name;
	std::string value;

	AttributeNode(std::string, std::string);
};

struct TextNode: public Node {
	TextNode(std::string);
};

struct ElementNode: public Node {
	std::vector<AttributeNode*> attributes;

	ElementNode(std::string);
	~ElementNode();

	void setAttribute(std::string, std::string);
	void setAttribute(AttributeNode& attribute);
	std::string getAttribute(std::string);
	void createTextNode(std::string);
	std::string outerHTML();
};
