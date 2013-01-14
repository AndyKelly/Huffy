/*
 * HuffyCompressor.cpp
 *
 *      Author: Andy Kelly
 */

#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyBaseType.h"
#include "SocketException.h"
#include "TreeUtility.h"
#include "BitString.h"
#include "HuffyBaseType.h"
#include "HuffyBool.h"
#include "HuffyFloat.h"
#include "HuffyInt.h"
#include <iostream>
#include <string>
#include <list>
#include <bitset>
#include <map>
#include <math.h>



//Static init
bool HuffyCompressor::m_Adapted = false;
HuffyTreeManager HuffyCompressor::m_TreeManager;
HuffyPacker HuffyCompressor::m_Packer;

HuffyCompressor::HuffyCompressor(void)
{
}

HuffyCompressor::~HuffyCompressor(void)
{

}

void HuffyCompressor::Adapt()
{
	m_Adapted = true;
}

//Todo, Impliment in next iteration
//Todo, this function is messy, consider abstracting to new class
//To be done in next iteration
void HuffyCompressor::ApplyUpdate(std::map<std::string, const HuffyBaseType* > HuffyPtrMap,
		std::map<std::string, HuffyInt* > HuffyIntPtrMap,
		std::map<std::string, HuffyFloat* > HuffyFloatPtrMap,
		std::map<std::string, HuffyBool* > HuffyBoolPtrMap,
		std::string UpdateToApply)
{
/*
	m_Packer.ApplyUpdateString(UpdateToApply);

	std::string Update = m_Packer.GetUpdateAsBitsetString().GetValue();

	std::string UpdateReference = Update;
	e_HuffyTypes RetrievedType;
	int StringCounter = 0;
	int IndexCounter = 0;

	while (RetrievedType != e_EndOfMessage)
	{
		Traverse type tree using BitString until found type, store
		RetrievedType = m_TreeManager.GetTypeFromString(Update);
		Update = TrimStringToIndex_Inclusive(Update, StringCounter);
		std::cout << "GotType" << RetrievedType;
		StringCounter = 0;

		if (RetrievedType != e_EndOfMessage)
		{

			if(RetrievedType == e_AdaptRequest)
			{
				HuffyManager::Adapt();
				m_Adapted = false;
				StringCounter = 0;
			}
			Use BitString to get ID
			std::string ID = m_TreeManager.GetIDFromStringByType(Update,RetrievedType);
			Update = TrimStringToIndex_Inclusive(Update,StringCounter);
			switch type
			switch (RetrievedType)
			{
			case (e_HuffyInt):
				{
				Traverse BitsUsed tree using BitString until found BitsUsed, store
					int BitsUsed = m_TreeManager.GetBitsUsedFromString(Update);
					Update = TrimStringToIndex_Inclusive(Update,StringCounter);
				//Todo, point of failure here, check it
					IndexCounter = UpdateReference.length() - Update.length();
					int Value = m_Packer.ReadIntAtIndex(BitsUsed, IndexCounter);
					HuffyIntPtrMap[ID]->SetValue(Value);
				//Erase up to IndexCounter + BitsUsed
					Update = TrimStringToIndex_Inclusive(Update,(IndexCounter + BitsUsed));
				StringCounter = 0;
				break;
			}
			case (e_HuffyFloat):
				{
				Traverse BitsUsed tree using BitString until found BitsUsed, store
					int BitsUsed = m_TreeManager.GetBitsUsedFromString(Update);
					Update = TrimStringToIndex_Inclusive(Update,StringCounter);
				//Todo, point of failure here, check it
					IndexCounter = UpdateReference.length() - Update.length();
					float Value = m_Packer.ReadFloatAtIndex(BitsUsed, IndexCounter);
					HuffyFloatPtrMap[ID]->SetValue(Value);
				//Erase up to IndexCounter + BitsUsed
					Update = TrimStringToIndex_Inclusive(Update,(IndexCounter + BitsUsed));
				StringCounter = 0;
				break;
				}
			case (e_HuffyBool):
				{
				//Todo, point of failure here, check it
					IndexCounter = UpdateReference.length() - Update.length();
					bool Value = m_Packer.ReadBoolAtIndex(IndexCounter);
					HuffyBoolPtrMap[ID]->SetValue(Value);
				//Erase up to IndexCounter + BitsUsed
					Update = TrimStringToIndex_Inclusive(Update,(IndexCounter + 1));
				StringCounter = 0;
				break;
				}
			}

			RetrievedType = e_EndOfMessage;
		}
	}
	*/
}


std::string HuffyCompressor::TrimStringToIndex_Inclusive(std::string StringToTrim,int index)
{
	std::string::iterator it;
	it=StringToTrim.begin()+index;
	StringToTrim.erase(it, StringToTrim.end());
	return StringToTrim;
}

std::string HuffyCompressor::ConstructUpdateFromIDList(
		std::list<std::string> ID_List,
		std::map<std::string, HuffyInt* > HuffyIntPtrMap,
		std::map<std::string, HuffyFloat* > HuffyFloatPtrMap,
		std::map<std::string, HuffyBool* > HuffyBoolPtrMap,
		std::map<std::string, e_HuffyTypes > ID_TpyeAssociationMap
		)
{
	std::cout<< "Attempting To Construct Update, Number of elements in IDlist:\n" << ID_List.size();

	for (std::list<std::string>::iterator it = ID_List.begin(); it != ID_List.end(); it++)
	{
		std::string IDToAdd = *it;
		try
		{
			switch(ID_TpyeAssociationMap[IDToAdd])
			{
				case e_HuffyInt:
				{
					HuffyInt* HuffyIntPointer = HuffyIntPtrMap[IDToAdd] ;
					std::cout << "\nAdding Int with ID:" <<HuffyIntPointer->GetID() << "and Value:"<< HuffyIntPointer->GetValue_C()<<"\n";
					AddIntToUpdate(IDToAdd,	HuffyIntPointer->GetValue_C());
					std::cout<<"Fully Encoded BitString is now:\n";
					std::cout << m_Packer.GetUpdateAsBitsetString().GetValue()<<"\n";
					break;
				}
				case e_HuffyFloat:
				{

					HuffyFloat* HuffyFloatPointer = HuffyFloatPtrMap[IDToAdd] ;
					std::cout << "\nAdding Float with ID:" <<HuffyFloatPointer->GetID()<< "and Value:"<<HuffyFloatPointer->GetValue()<<"\n";
					AddFloatToUpdate(IDToAdd,HuffyFloatPointer->GetValue_C());
					std::cout<<"\nFully Encoded BitString is now:\n";
					std::cout << m_Packer.GetUpdateAsBitsetString().GetValue()<<"\n";

					break;
				}
				case e_HuffyBool:
				{
					HuffyBool* HuffyBoolPointer = HuffyBoolPtrMap[IDToAdd] ;
					std::cout << "\nAdding Bool with ID:" <<HuffyBoolPointer->GetID()<< "and Value:"<<HuffyBoolPointer->GetValue_C()<<"\n";
					AddBoolToUpdate(IDToAdd,HuffyBoolPointer->GetValue_C());
					std::cout<<"\nFully Encoded BitString is now:\n";
					std::cout << m_Packer.GetUpdateAsBitsetString().GetValue()<<"\n";
					break;
				}
			}

		}
	    catch (...)
	    {
			//Todo some way of logging this error
	    	std::cout << "Something went wrong";
	    }

	}

	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForType(e_EndOfMessage).GetValue());

    std::string ReturnString = m_Packer.ReturnUpdateString();
    //Todo impliment adaptions in next iteration
    //if(m_Adapted)
    //{
    //	ReturnString = m_TreeManager.GetBitStringForType(e_AdaptRequest).GetValue() + ReturnString;
    //	m_Adapted = false;
    //}

    //Add end of message to string;
    std::cout << "\nUpdate is:"<< ReturnString <<"END";
    return ReturnString;
}


void HuffyCompressor::AddIntToUpdate(std::string IDToAdd, int Value)
{
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForType(e_HuffyInt).GetValue());
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForID(IDToAdd,e_HuffyInt).GetValue());
	int SizeInBits = m_Packer.HowBigIsThisInt(Value);
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForBitsUsed(SizeInBits).GetValue());
	m_Packer.AddIntValueToUpdate( Value, SizeInBits);
}

void HuffyCompressor::AddFloatToUpdate(std::string IDToAdd, float Value)
{
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForType(e_HuffyFloat).GetValue());
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForID(IDToAdd,e_HuffyFloat).GetValue());
	int SizeInBits = m_Packer.HowBigIsThisFloat(Value);
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForBitsUsed(SizeInBits).GetValue());
	m_Packer.AddFloatValueToUpdate(SizeInBits, Value);
}

void HuffyCompressor::AddBoolToUpdate(std::string IDToAdd, bool Value)
{
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForType(e_HuffyBool).GetValue());
	m_Packer.WriteBitsetStyleStringToBuffer(m_TreeManager.GetBitStringForID(IDToAdd,e_HuffyBool).GetValue());
	m_Packer.AddBoolValueToUpdate(Value);
}


void HuffyCompressor::PassPointersToHuffyTreeRootNodes(TypeQueueElement* NewTypeTree,
	IDQueueElement* NewIntIdTree,
	IDQueueElement* NewFloatIDTree,
	IDQueueElement* NewBoolIDTree,
	BitsUsedQueueElement* NewBitsUsedIDTree )
{
	m_TreeManager.PassPointersToHuffyTreeRootNodes(NewTypeTree,NewIntIdTree,NewFloatIDTree,NewBoolIDTree,NewBitsUsedIDTree);
}



int HuffyCompressor::HowManyBitsToStoreThis(int Value)
{
	return m_Packer.HowBigIsThisInt(Value);
}

int HuffyCompressor::HowManyBitsToStoreThis(float Value)
{
	return m_Packer.HowBigIsThisFloat(Value);
}
