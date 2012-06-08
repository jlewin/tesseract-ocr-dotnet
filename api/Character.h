/**
Copyright 2011, Cong Nguyen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#pragma once

#include "Configuration.h"
#include "RecognitionItem.h";
#include "resultiterator.h";

BEGIN_NAMSPACE

USING_COMMON_SYSTEM

__gc public class Character : public RecognitionItem
{
public:
	Character();
	~Character();

public:
	String* Value;
	List<String*>* Variants;

public:

	//ResultIterator* resultIterator = dynamic_cast(pageIterator);
	//		if (resultIterator!=null)
	//		{

	//		}

	void CollectResult(PageIterator* pageIterator)
	{
		ResultIterator* resultIterator = dynamic_cast<ResultIterator*>(pageIterator);
		if (resultIterator!=null)
		{
			ChoiceIterator* choiceIterator = null;
	
			try
			{
				choiceIterator = new ChoiceIterator(*resultIterator);
				
				do
				{
					const char* choiceValue = choiceIterator->GetUTF8Text();
					if (choiceValue!=NULL)
						Variants->Add(new String(choiceValue, 0, strlen(choiceValue), Encoding::UTF8));


				} while (choiceIterator->Next());

			}
			__finally
			{
				SAFE_DELETE(choiceIterator);
			}
		}
		RecognitionItem::CollectResult(pageIterator);
	}

	//// Constructor
	//Character(char character, 
	//	int left, int top, int right, int bottom)
	//	: RecognitionItem(left, top, right, bottom)
	//{
	//	Value = character;
	//	_pageLevel = ePageLevel::RIL_SYMBOL;

	//	_color = System::Drawing::Color::Blue;
	//}

	//// Constructor
	//Character(char character, double confidence, 
	//	int left, int top, int right, int bottom) 
	//	: RecognitionItem(confidence, left, top, right, bottom)
	//{
	//	Value = character;
	//	_pageLevel = ePageLevel::RIL_SYMBOL;

	//	_color = System::Drawing::Color::Blue;
	//}
	
protected:
	PageIteratorLevel GetNextPageIteratorLevel()
	{
		return PageIteratorLevel::RIL_SYMBOL;
	}
};



END_NAMESPACE