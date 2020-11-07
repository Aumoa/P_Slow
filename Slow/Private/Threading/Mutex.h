// Copyright 2020 Team slow. All right reserved.

#pragma once



class FMutex;

class FMutexSafeLockState
{
	TSharedPtr<FMutex> MutexPtr;

public:
	FMutexSafeLockState();
	FMutexSafeLockState( TSharedPtr<FMutex> Mutex );
	FMutexSafeLockState( FMutexSafeLockState&& Move );
	~FMutexSafeLockState();
	
	void Resign();

	FMutexSafeLockState& operator=( FMutexSafeLockState&& Move );
};

class FMutex : public TSharedFromThis<FMutex>
{
	FCriticalSection CriticalSection;
	bool bLock;

public:
	FMutex();
	~FMutex();

	FMutexSafeLockState Lock();
	bool TryLock( FMutexSafeLockState& Context );
	void Unlock();

	bool IsLock() const;
};
