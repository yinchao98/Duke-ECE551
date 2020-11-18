#include "node.h"

Node *  buildTree(uint64_t * counts) {
	priority_queue_t pq;
	for(size_t i = 0; i < 257; i++) {
		if(counts[i] != 0) {
			pq.push(new Node(i, counts[i]));
		}
	}
	if(pq.empty()) {
		return NULL;
	}
	while(pq.size() != 1) {
		Node *node1 = pq.top();
		pq.pop();
		Node *node2 = pq.top();
		pq.pop();
		pq.push(new Node(node1, node2));
	}
	return pq.top();
}
