// Copyright 2020 Team slow. All right reserved.

#include "Threading/Mutex.h"

#include "LogDefine.h"

FMutexSafeLockState::FMutexSafeLockState()
{

}

FMutexSafeLockState::FMutexSafeLockState( TSharedPtr<FMutex> Mutex )
{
	MutexPtr = Mutex;
}

FMutexSafeLockState::FMutexSafeLockState( FMutexSafeLockState&& Move )
{
	MutexPtr = std::move( Move.MutexPtr );
}

FMutexSafeLockState::~FMutexSafeLockState()
{
	if ( MutexPtr.IsValid() )
	{
		MutexPtr->Unlock();
	}
}

void FMutexSafeLockState::Resign()
{
	MutexPtr = nullptr;
}

FMutexSafeLockState& FMutexSafeLockState::operator=( FMutexSafeLockState&& Move )
{
	MutexPtr = std::move( Move.MutexPtr );
	return *this;
}

FMutex::FMutex()
{
	bLock = false;
}

FMutex::~FMutex()
{
	Unlock();
}

FMutexSafeLockState FMutex::Lock()
{
	CriticalSection.Lock();
	bLock = true;
	return AsShared();
}

bool FMutex::TryLock( FMutexSafeLockState& Context )
{
	bool bLock_ = CriticalSection.TryLock();
	this->bLock = bLock_;

	if ( bLock_ )
	{
		Context = std::move( FMutexSafeLockState( AsShared() ) );
	}

	return bLock_;
}

void FMutex::Unlock()
{
	if ( !IsLock() ) return;

	if ( bLock )
	{
		CriticalSection.Unlock();
	}
}

bool FMutex::IsLock() const
{
	return bLock;
}