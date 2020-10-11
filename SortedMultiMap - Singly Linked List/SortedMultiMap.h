#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TValue);

class SortedMultiMap {
	friend class SMMIterator;
	struct SLLNode {
	    TValue value;
	    SLLNode* next;
	};
	struct SLLList {
	    SLLNode* head;
	    int size;
	    SLLList() {
	        head = nullptr;
	        size = 0;
	    }
	    ~SLLList() {
	    	while (head != nullptr) {
	    		auto current = head;
	    		head = head->next;
			    delete current;
		    }
	    }
	};
	struct IteratorSLLList {
	    SLLList* list;
	    SLLNode* current;
	    explicit IteratorSLLList(SLLList* list1) {
	    	current = nullptr;
	    	list = list1;
	    	if (list1 != nullptr) {
				current = list->head;
	    	}
	    }
	};
	struct SMMNode {
	    TKey key{};
	    SLLList* list;
	    SMMNode* next;
	    SMMNode() {
	        next = nullptr;
	        list = new SLLList;
	    }
	    ~SMMNode() {
	    	delete list;
	    }
	};
    private:
		SMMNode* head;
        Relation rel;

        void addList(SMMNode*, TValue val);

        bool removeList(SMMNode* node,  TValue val);

        int sizeList(SMMNode* node) const;

        IteratorSLLList iteratorList(SMMNode* node);

        static void firstList(IteratorSLLList& it);

        static bool validList(IteratorSLLList& it);

        static void nextList(IteratorSLLList& it);

        static TValue getCurrentList(IteratorSLLList it);

    public:

    // constructor
    explicit SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

	//removes a key together with all its values
	//returns a vector with the values that were previously associated to this value (and were removed)
	vector<TValue> removeKey(TKey key);

    // destructor
    ~SortedMultiMap();
};
