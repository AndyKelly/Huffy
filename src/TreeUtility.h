/*
 * TreeUtility.h
 *
 *      Author: Andy Kelly
 */

#ifndef TREEUTILITY_H_
#define TREEUTILITY_H_
#include "HuffyConstants.h"


	struct TypeQueueElement
	{
		TypeQueueElement(e_HuffyTypes TypeValue,
			long long Frequency,
			TypeQueueElement* LeftChild,
			TypeQueueElement* RightChild,
			TypeQueueElement* Parent)
		{
			m_TypeValue = TypeValue;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		e_HuffyTypes m_TypeValue;
		long long m_Frequency;
		TypeQueueElement* m_LeftChild;
		TypeQueueElement* m_RightChild;
		TypeQueueElement* m_Parent;
	};
	struct IDQueueElement
	{
		IDQueueElement(std::string ID,
			long long Frequency,
			IDQueueElement* LeftChild,
			IDQueueElement* RightChild,
			IDQueueElement* Parent)
		{
			m_ID = ID;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		std::string m_ID;
		long long m_Frequency;
		IDQueueElement* m_LeftChild;
		IDQueueElement* m_RightChild;
		IDQueueElement* m_Parent;
	};
	struct BitsUsedQueueElement
	{
		BitsUsedQueueElement(int BitsUsed,
			long long Frequency,
			BitsUsedQueueElement* LeftChild,
			BitsUsedQueueElement* RightChild,
			BitsUsedQueueElement* Parent)
		{
			m_BitsUsed = BitsUsed;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		int m_BitsUsed;
		long long m_Frequency;
		BitsUsedQueueElement* m_LeftChild;
		BitsUsedQueueElement* m_RightChild;
		BitsUsedQueueElement* m_Parent;
	};

	class CompareTypeElements
	{
		public:
		bool operator()(TypeQueueElement& Q1, TypeQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};
	class CompareIDElements
	{
		public:
		bool operator()(IDQueueElement& Q1, IDQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};
	class CompareBitsUsedElements
	{
		public:
		bool operator()(BitsUsedQueueElement& Q1, BitsUsedQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};


#endif /* TREEUTILITY_H_ */
