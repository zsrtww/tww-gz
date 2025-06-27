#ifndef JSULIST_H
#define JSULIST_H

#include "../../dolphin/gctypes.h"
#include <cstddef>

// Forward declaration
template <typename T>
class JSUList;

//
// Link
//

class JSUPtrList;
class JSUPtrLink {
public:
    explicit JSUPtrLink(void* object = nullptr)
        : mObject(object), mList(nullptr), mPrev(nullptr), mNext(nullptr) {}

    void* getObjectPtr() const { return mObject; }
    JSUPtrList* getList() const { return mList; }
    JSUPtrLink* getNext() const { return mNext; }
    JSUPtrLink* getPrev() const { return mPrev; }

    // Donne accès direct aux membres protégés pour JSUPtrList & co.
    friend class JSUPtrList;

protected:
    void*       mObject;
    JSUPtrList* mList;
    JSUPtrLink* mPrev;
    JSUPtrLink* mNext;
};

template <typename T>
class JSULink : public JSUPtrLink {
public:
    explicit JSULink(T* object) : JSUPtrLink(static_cast<void*>(object)) {}

    T* getObject() const { return static_cast<T*>(getObjectPtr()); }
    JSUList<T>* getSupervisor() const { return static_cast<JSUList<T>*>(this->getList()); }
    JSULink<T>* getNext() const { return static_cast<JSULink<T>*>(this->JSUPtrLink::getNext()); }
    JSULink<T>* getPrev() const { return static_cast<JSULink<T>*>(this->JSUPtrLink::getPrev()); }
};

//
// List
//

class JSUPtrList {
public:
    JSUPtrList() : mHead(nullptr), mTail(nullptr), mLength(0) {}

    // --- Mutators ---------------------------------------------------------
    bool append(JSUPtrLink* link) {
        if (!link) return false;
        if (link->mList) link->mList->remove(link);  // détacher si déjà dans une liste

        link->mPrev = mTail;
        link->mNext = nullptr;
        link->mList = this;

        if (mTail)
            mTail->mNext = link;
        else
            mHead = link;

        mTail = link;
        ++mLength;
        return true;
    }

    bool prepend(JSUPtrLink* link) {
        if (!link) return false;
        if (link->mList) link->mList->remove(link);

        link->mPrev = nullptr;
        link->mNext = mHead;
        link->mList = this;

        if (mHead)
            mHead->mPrev = link;
        else
            mTail = link;

        mHead = link;
        ++mLength;
        return true;
    }

    bool insert(JSUPtrLink* before, JSUPtrLink* link) {
        if (!link) return false;
        if (!before) return append(link);
        if (before->mList != this) return false; // "before" n'appartient pas à cette liste

        if (link->mList) link->mList->remove(link);

        link->mPrev = before->mPrev;
        link->mNext = before;
        link->mList = this;

        if (before->mPrev)
            before->mPrev->mNext = link;
        else
            mHead = link;

        before->mPrev = link;
        ++mLength;
        return true;
    }

    bool remove(JSUPtrLink* link) {
        if (!link || link->mList != this) return false;

        if (link->mPrev)
            link->mPrev->mNext = link->mNext;
        else
            mHead = link->mNext;

        if (link->mNext)
            link->mNext->mPrev = link->mPrev;
        else
            mTail = link->mPrev;

        link->mPrev = link->mNext = nullptr;
        link->mList = nullptr;
        --mLength;
        return true;
    }

    // --- Accessors --------------------------------------------------------
    JSUPtrLink* getFirstLink() const { return mHead; }
    JSUPtrLink* getLastLink()  const { return mTail; }
    u32         getNumLinks()  const { return mLength; }

protected:
    JSUPtrLink* mHead;
    JSUPtrLink* mTail;
    u32         mLength;
};

template <typename T>
class JSUList : public JSUPtrList {
public:
    JSUList() : JSUPtrList() {}

    bool append(JSULink<T>* link)               { return this->JSUPtrList::append(static_cast<JSUPtrLink*>(link)); }
    bool prepend(JSULink<T>* link)              { return this->JSUPtrList::prepend(static_cast<JSUPtrLink*>(link)); }
    bool insert(JSULink<T>* before, JSULink<T>* link) { return this->JSUPtrList::insert(static_cast<JSUPtrLink*>(before), static_cast<JSUPtrLink*>(link)); }
    bool remove(JSULink<T>* link)               { return this->JSUPtrList::remove(static_cast<JSUPtrLink*>(link)); }

    JSULink<T>* getFirst() const { return static_cast<JSULink<T>*>(getFirstLink()); }
    JSULink<T>* getLast()  const { return static_cast<JSULink<T>*>(getLastLink());  }
    JSULink<T>* getEnd()   const { return nullptr; }

    u32 getNumLinks() const { return this->JSUPtrList::getNumLinks(); }
};

//
// List iterator
//

template <typename T>
class JSUListIterator {
public:
    JSUListIterator() : mLink(nullptr) {}
    explicit JSUListIterator(JSULink<T>* link) : mLink(link) {}
    explicit JSUListIterator(JSUList<T>* list) : mLink(list ? list->getFirst() : nullptr) {}

    JSUListIterator<T>& operator=(JSULink<T>* link) { mLink = link; return *this; }

    T* getObject() { return mLink ? mLink->getObject() : nullptr; }

    bool operator==(JSULink<T> const* other)   const { return mLink == other; }
    bool operator!=(JSULink<T> const* other)   const { return mLink != other; }
    bool operator==(JSUListIterator<T> const& other) const { return mLink == other.mLink; }
    bool operator!=(JSUListIterator<T> const& other) const { return mLink != other.mLink; }

    JSUListIterator<T> operator++(int) { JSUListIterator<T> prev = *this; if (mLink) mLink = mLink->getNext(); return prev; }
    JSUListIterator<T>& operator++()   { if (mLink) mLink = mLink->getNext(); return *this; }
    JSUListIterator<T> operator--(int) { JSUListIterator<T> prev = *this; if (mLink) mLink = mLink->getPrev(); return prev; }
    JSUListIterator<T>& operator--()   { if (mLink) mLink = mLink->getPrev(); return *this; }

    T& operator*()  { return *getObject(); }
    T* operator->() { return  getObject(); }

private:
    JSULink<T>* mLink;
};

//
// Tree
//

#define JSU_TREE_FROM_LINK(T, LINK) (reinterpret_cast<JSUTree<T>*>(reinterpret_cast<u8*>(LINK) - 12))
#define JSU_TREE_LINK_IF_NOT_NULL(TREE) if (TREE) { TREE = reinterpret_cast<JSUTree<T>*>(&(TREE)->mLink); }
#define _JSU_TREE_AS_LINK(TREE) (reinterpret_cast<JSULink<T>*>(TREE))

template <typename T>
class JSUTree : public JSUList<T>, public JSULink<T> {
public:
    explicit JSUTree(T* owner) : JSUList<T>(), JSULink<T>(owner) {}
    ~JSUTree() {}

    bool appendChild(JSUTree<T>* child)                     { return this->append(child); }
    bool removeChild(JSUTree<T>* child)                     { return this->remove(child); }
    bool insertChild(JSUTree<T>* before, JSUTree<T>* child) { return this->insert(before, child); }

    JSUTree<T>* getEndChild()   const { return nullptr; }
    JSUTree<T>* getFirstChild() const { return static_cast<JSUTree<T>*>(this->getFirst()); }
    JSUTree<T>* getLastChild()  const { return static_cast<JSUTree<T>*>(this->getLast());  }
    JSUTree<T>* getNextChild()  const { return static_cast<JSUTree<T>*>(this->getNext());  }
    JSUTree<T>* getPrevChild()  const { return static_cast<JSUTree<T>*>(this->getPrev());  }

    u32          getNumChildren() const { return this->getNumLinks(); }
    T*           getObject()      const { return static_cast<T*>(this->getObjectPtr()); }
    JSUTree<T>*  getParent()      const { return static_cast<JSUTree<T>*>(this->getList()); }
};

//
// Tree iterator
//

template <typename T>
class JSUTreeIterator {
public:
    JSUTreeIterator() : mTree(nullptr) {}
    explicit JSUTreeIterator(JSUTree<T>* tree) : mTree(tree) {}

    JSUTreeIterator<T>& operator=(JSUTree<T>* tree) { mTree = tree; return *this; }

    T* getObject() { return mTree ? mTree->getObject() : nullptr; }

    bool operator==(JSUTree<T>* other) const { return mTree == other; }
    bool operator!=(JSUTree<T>* other) const { return mTree != other; }

    JSUTreeIterator<T> operator++(int) { JSUTreeIterator<T> prev = *this; if (mTree) mTree = mTree->getNextChild(); return prev; }
    JSUTreeIterator<T>& operator++()   { if (mTree) mTree = mTree->getNextChild(); return *this; }

    T& operator*()  { return *getObject(); }
    T* operator->() { return  getObject(); }

private:
    JSUTree<T>* mTree;
};

#endif /* JSULIST_H */