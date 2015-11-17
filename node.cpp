#include "node.h"

std::string Node::end[] = {
		"area", "base", "col", "command", "embed", "hr", "img", "input",
		"keygen", "link", "meta", "param", "source", "track", "wbr"};

Node::~Node() {}

void Node::appendChild(Node& node) {
	childNodes.push_back(&node);
	node.parentNode = this;
};

ElementNode::ElementNode(std::string name) {
	nodeName = name;
};

void ElementNode::setAttribute(std::string name, std::string value) {
	AttributeNode* attribute = new AttributeNode(name, value);
	setAttribute(*attribute);
};

void ElementNode::setAttribute(AttributeNode& attribute) {
	attributes.push_back(&attribute);
};

std::string ElementNode::getAttribute(std::string name) {
	for (unsigned i = 0; i < attributes.size(); ++i) {
		if (attributes[i]->nodeName.compare(name) == 0) {
			return attributes[i]->nodeValue;
		}
	}
	return "";
};

void ElementNode::createTextNode(std::string value) {
	TextNode* text = new TextNode(value);
	appendChild(*text);
};

std::string ElementNode::outerHTML() {
	std::string ret = "<" + nodeName;

	for (unsigned i = 0; i < attributes.size(); ++i) {
		ret += " " + attributes[i]->name + "=\"" + attributes[i]->value + "\"";
	}

	ret += ">";

	if (std::find(std::begin(Node::end), std::end(Node::end), nodeName) == std::end(Node::end)) {
		for (unsigned i = 0; i < childNodes.size(); ++i) {
			ElementNode* node = dynamic_cast<ElementNode*>(childNodes[i]);
			if (node != nullptr) {
				ret += node->outerHTML();
			}
			else {
				ret += childNodes[i]->nodeValue;
			}
		}
		ret += "</" + nodeName + ">";
	}

	return ret;
};

ElementNode::~ElementNode() {
	for (unsigned i = 0; i < attributes.size(); ++i) {
		delete attributes[i];
	}
};

TextNode::TextNode(std::string value) {
	nodeValue = value;
};

AttributeNode::AttributeNode(std::string name, std::string value) {
	this->name = name;
	this->value = value;
};
