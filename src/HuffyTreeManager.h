/*
 * HuffyTreeManager.h
 *
 *  Created on: Jan 13, 2013
 *      Author: hal
 */

#ifndef HUFFYTREEMANAGER_H_
#define HUFFYTREEMANAGER_H_
#include "TreeUtility.h"
#include "BitString.h"
class HuffyTreeManager {
public:
	HuffyTreeManager();
	~HuffyTreeManager();
	void PassPointersToHuffyTreeRootNodes(TypeQueueElement*,IDQueueElement* ,IDQueueElement* ,IDQueueElement*,BitsUsedQueueElement* );

	BitString GetBitStringForType(e_HuffyTypes);
	BitString GetBitStringForID(std::string, e_HuffyTypes);
	BitString GetBitStringForBitsUsed(int);
	e_HuffyTypes GetTypeFromString(std::string);
	int GetBitsUsedFromString(std::string);
	std::string GetIDFromStringByType(std::string, e_HuffyTypes);
	std::string GetIDFromString(std::string, IDQueueElement*);
private:

	TypeQueueElement* GetPointerToNodeInTypeTreeByType(e_HuffyTypes);
	IDQueueElement* GetPointerToNodeInIDTreeByIDAndType(std::string,e_HuffyTypes);
	IDQueueElement* GetPointerToNodeInIntIDTreeByID(std::string);
	IDQueueElement* GetPointerToNodeInFloatIDTreeByID(std::string);
	IDQueueElement* GetPointerToNodeInBoolIDTreeByID(std::string);
	BitsUsedQueueElement* GetPointerToNodeInBitsUsedTreeByValue(int);
	//Delete Tree's
	void DeleteOldTrees();
	void DeleteTypeQueueElementTree(TypeQueueElement*);
	void DeleteIDQueueElementTree(IDQueueElement*);
	void DeleteBitsUsedQueueElementTree(BitsUsedQueueElement*);
	TypeQueueElement* m_TypeTreeRootNode;
	IDQueueElement* m_IntIDTreeRootNode;
	IDQueueElement* m_FloatIDTreeRootNode;
	IDQueueElement* m_BoolIDTreeRootNode;
	BitsUsedQueueElement* m_BitsUsedTreeRootNode;
};

#endif /* HUFFYTREEMANAGER_H_ */
