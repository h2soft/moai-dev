// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	USLEANLIST_H
#define	USLEANLIST_H

template < typename TYPE > class USLeanList;
template < typename TYPE > class USList;

//================================================================//
// USLeanLink
//================================================================//
template < typename TYPE >
class USLeanLink {
private:

	TYPE					mData;
	USLeanLink < TYPE >*	mPrev;
	USLeanLink < TYPE >*	mNext;
	USLeanList < TYPE >*	mList;

public:

	friend class USLeanList < TYPE >;
	friend class USList < TYPE >;

	//----------------------------------------------------------------//
	inline TYPE& Data () {
		return this->mData;
	}

	//----------------------------------------------------------------//
	inline void Data ( const TYPE& data ) {
		this->mData = data;
	}

	//----------------------------------------------------------------//
	inline void Remove () {
		if ( this->mList ) {
			this->mList->Remove ( *this );
		}
	}

	//----------------------------------------------------------------//
	inline USLeanLink < TYPE >* Next () {
		return ( this->mNext ) ? this->mNext : 0;
	}
	
	//----------------------------------------------------------------//
	inline USLeanLink < TYPE >* Prev () {
		return ( this->mPrev ) ? this->mPrev : 0;
	}
	
	//----------------------------------------------------------------//
	USLeanLink () :
		mPrev ( 0 ),
		mNext ( 0 ),
		mList ( 0 ) {
	}

	//----------------------------------------------------------------//
	USLeanLink ( const TYPE& data ) :
		mData ( data ),
		mPrev ( 0 ),
		mNext ( 0 ),
		mList ( 0 ) {
	}
	
	//----------------------------------------------------------------//
	~USLeanLink ()  {
		this->Remove ();
	}
};

//================================================================//
// USLeanList
//================================================================//
template < typename TYPE >
class USLeanList {
private:

	USLeanLink < TYPE >*	mHead;
	USLeanLink < TYPE >*	mTail;
	u32						mCount;

public:

	typedef USLeanLink < TYPE >* Iterator;

	//----------------------------------------------------------------//
	inline TYPE& Back () {
		assert ( this->mTail );
		return this->mTail->Data ();
	}

	//----------------------------------------------------------------//
	void Clear () {
		
		this->mCount = 0;
		this->mHead = 0;
		this->mTail = 0;
	}

	//----------------------------------------------------------------//
	u32 Count () {
		return this->mCount;
	}

	//----------------------------------------------------------------//
	USLeanLink < TYPE >* FindFirst ( const TYPE& type ) {
	
		Iterator iterator = this->Head ();
		for ( ; iterator ; iterator = iterator->Next ()) {
			if ( iterator->Data () == type ) {
				return iterator;
			}
		}
		return 0;
	}

	//----------------------------------------------------------------//
	USLeanLink < TYPE >* FindLast ( const TYPE& type ) {
	
		Iterator iterator = this->Tail ();
		for ( ; iterator ; iterator = iterator->Prev ()) {
			if ( iterator->Data () == type ) {
				return iterator;
			}
		}
		return 0;
	}

	//----------------------------------------------------------------//
	inline TYPE& Front () {
		assert ( this->mHead );
		return this->mHead->Data ();
	}

	//----------------------------------------------------------------//
	void Join ( USLeanList < TYPE >& a, USLeanList < TYPE >& b ) {
	
		USLeanLink < TYPE >* headA = a.mHead;
		USLeanLink < TYPE >* tailA = a.mTail;
		
		USLeanLink < TYPE >* headB = b.mHead;
		USLeanLink < TYPE >* tailB = b.mTail;
		
		u32 count = a.mCount + b.mCount;
		
		this->Clear ();
		a.Clear ();
		b.Clear ();
		
		if ( tailA ) {
			tailA->mNext = headB;
		}
		
		if ( headB ) {
			headB->mPrev = tailA;
		}
		
		this->mHead = headA ? headA : headB;
		this->mTail = tailB ? tailB : tailA;
		this->mCount = count;
	}

	//----------------------------------------------------------------//
	inline USLeanLink < TYPE >* Head () {
		return ( this->mHead ) ? this->mHead : 0;
	}

	//----------------------------------------------------------------//
	void InsertAfter ( USLeanLink < TYPE >& cursor, USLeanLink < TYPE >& link ) {

		link.Remove ();

		if ( cursor.mNext ) {
		
			link.mPrev = &cursor;
			link.mNext = cursor.mNext;
		
			link.mPrev->mNext = &link;
			link.mNext->mPrev = &link;
		}
		else {
			this->PushBack ( link );
		}
		
		link.mList = this;
		++this->mCount;
	}

	//----------------------------------------------------------------//
	void InsertBefore ( USLeanLink < TYPE >& cursor, USLeanLink < TYPE >& link ) {

		link.Remove ();

		if ( cursor.mPrev ) {
			
			link.mPrev = cursor.mPrev;
			link.mNext = &cursor;
		
			link.mPrev->mNext = &link;
			link.mNext->mPrev = &link;
		}
		else {
			this->PushFront ( link );
		}
		
		link.mList = this;
		++this->mCount;
	}

	//----------------------------------------------------------------//
	void PopBack () {
	
		if ( this->mTail ) {
			this->Remove ( *this->mTail );
		}
	}

	//----------------------------------------------------------------//
	void PopFront () {
	
		if ( this->mHead ) {
			this->Remove ( *this->mHead );
		}
	}

	//----------------------------------------------------------------//
	void PushBack ( USLeanLink < TYPE >& link ) {

		link.Remove ();

		if ( !mHead ) {
			this->mHead = &link;
			this->mTail = &link;
			link.mPrev = 0;
			link.mNext = 0;
		}
		else {
			this->mTail->mNext = &link;
			link.mPrev = mTail;
			link.mNext = 0;
			this->mTail = &link;
		}

		link.mList = this;
		++this->mCount;
	}

	//----------------------------------------------------------------//
	void PushFront ( USLeanLink < TYPE >& link ) {

		link.Remove ();

		if ( !this->mHead ) {
			this->mHead = &link;
			this->mTail = &link;
			link.mPrev = 0;
			link.mNext = 0;
		}
		else {
			this->mHead->mPrev = &link;
			link.mPrev = 0;
			link.mNext = this->mHead;
			this->mHead = &link;
		}
		
		link.mList = this;
		++this->mCount;
	}

	//----------------------------------------------------------------//
	void Remove ( USLeanLink < TYPE >& link ) {

		if ( link.mList != this ) return;

		if ( link.mNext ) {
			link.mNext->mPrev = link.mPrev;
		}
		else {
			this->mTail = link.mPrev;
		}

		if ( link.mPrev ) {
			link.mPrev->mNext = link.mNext;
		}
		else {
			this->mHead = link.mNext;
		}
		
		link.mPrev = 0;
		link.mNext = 0;
		link.mList = 0;
		
		--this->mCount;
	}
	
	//----------------------------------------------------------------//
	inline USLeanLink < TYPE >* Tail () {
		return ( this->mTail ) ? this->mTail : 0;
	}
	
	//----------------------------------------------------------------//
	USLeanList () :
		mHead ( 0 ),
		mTail ( 0 ),
		mCount ( 0 ) {
	}
	
	//----------------------------------------------------------------//
	~USLeanList () {
		this->Clear ();
	}
};

#endif
