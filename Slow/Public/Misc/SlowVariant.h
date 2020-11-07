// Copyright 2020 Team slow. All right reserved.

#pragma once



namespace Variant_Impl
{
	template<class T, class... Args>
	inline constexpr size_t Max(T Pick1, T Pick2, Args&&... _Args)
	{
		return Max(Pick1 > Pick2 ? Pick1 : Pick2, _Args...);
	}

	template<class T>
	inline constexpr size_t Max(T Pick1, T Pick2)
	{
		return Pick1 > Pick2 ? Pick1 : Pick2;
	}

	template<class Desired, class T, class O, class... Args>
	inline constexpr size_t GetIndexImpl(size_t Start)
	{
		return TIsSame<Desired, T>::Value ? Start : GetIndexImpl<Desired, O, Args...>(Start + 1);
	}

	template<class Desired, class T>
	inline constexpr size_t GetIndexImpl(size_t Start)
	{
		return TIsSame<Desired, T>::Value ? Start : -1;
	}

	template<class T, class O, class... Args>
	inline void CopyConstruct(size_t Index, int8* Dest, const int8* Source)
	{
		if (Index == 0) {
			new(Dest) T(*(const T*)Source);
		}
		else {
			CopyConstruct<O, Args...>(Index - 1, Dest, Source);
		}
	}

	template<class T>
	inline void CopyConstruct(size_t Index, int8* Dest, const int8* Source)
	{
		if (Index == 0) {
			new(Dest) T(*(const T*)Source);
		}
		else {
			checkf(false, TEXT("error: Type not contains to variant."));
		}
	}

	template<class T, class O, class... Args>
	inline void MoveConstruct(size_t Index, int8* Dest, int8* Source)
	{
		if (Index == 0) {
			new(Dest) T(MoveTemp(*(T*)Source));
		}
		else {
			MoveConstruct<O, Args...>(Index - 1, Dest, Source);
		}
	}

	template<class T>
	inline void MoveConstruct(size_t Index, int8* Dest, int8* Source)
	{
		if (Index == 0) {
			new(Dest) T(MoveTemp(*(T*)Source));
		}
		else {
			checkf(false, TEXT("error: Type not contains to variant."));
		}
	}

	template<class T, class O, class... Args>
	inline void Destruct(size_t Index, int8* Dest)
	{
		if (Index == 0) {
			((T*)Dest)->~T();
		}
		else {
			Destruct<O, Args...>(Index - 1, Dest);
		}
	}

	template<class T>
	inline void Destruct(size_t Index, int8* Dest)
	{
		if (Index == 0) {
			((T*)Dest)->~T();
		}
		else {
			checkf(false, TEXT("error: Type not contains to variant."));
		}
	}

	template<class T, class O, class... Args>
	inline void Copy(size_t Index, int8* Dest, const int8* Source)
	{
		if (Index == 0) {
			*((T*)Dest) = *(const T*)Source;
		}
		else {
			Copy<O, Args...>(Index - 1, Dest, Source);
		}
	}

	template<class T>
	inline void Copy(size_t Index, int8* Dest, const int8* Source)
	{
		if (Index == 0) {
			*((T*)Dest) = *(const T*)Source;
		}
		else {
			checkf(false, TEXT("error: Type not contains to variant."));
		}
	}

	template<class T, class O, class... Args>
	inline void Move(size_t Index, int8* Dest, int8* Source)
	{
		if (Index == 0) {
			*((T*)Dest) = MoveTemp(*(const T*)Source);
		}
		else {
			Move<O, Args...>(Index - 1, Dest, Source);
		}
	}

	template<class T>
	inline void Move(size_t Index, int8* Dest, int8* Source)
	{
		if (Index == 0) {
			*((T*)Dest) = MoveTemp(*(const T*)Source);
		}
		else {
			checkf(false, TEXT("error: Type not contains to variant."));
		}
	}
}

template<class... T>
class TSlowVariant
{
	static constexpr size_t InvalidIndex = -1;

	int8 Bytes[Variant_Impl::Max(sizeof(T)...)];
	size_t Index = InvalidIndex;

public:
	TSlowVariant()
	{

	}

	TSlowVariant(const TSlowVariant& InCopy)
	{
		Variant_Impl::CopyConstruct<T...>(InCopy.Index, Bytes, InCopy.Bytes);
		Index = InCopy.Index;
	}

	TSlowVariant(TSlowVariant&& InMove)
	{
		Variant_Impl::MoveConstruct<T...>(InMove.Index, Bytes, InMove.Bytes);
		Index = InMove.Index;
	}

	template<class O>
	TSlowVariant(const O& TCopy)
	{
		using Other = std::remove_reference_t<O>;

		new(Bytes) Other(TCopy);
		Index = Variant_Impl::GetIndexImpl<Other, T...>(0);
	}

	template<class O>
	TSlowVariant(O&& TMove)
	{
		using Other = std::remove_reference_t<O>;

		new(Bytes) Other(TMove);
		Index = Variant_Impl::GetIndexImpl<Other, T...>(0);
	}

	~TSlowVariant()
	{
		if (Index != InvalidIndex) {
			Variant_Impl::Destruct<T...>(Index, Bytes);
			Index = InvalidIndex;
		}
	}

	size_t GetIndex() const
	{
		return Index;
	}

	bool IsValid() const
	{
		return Index != InvalidIndex;
	}

	template<class O>
	bool IsValidType() const
	{
		return Variant_Impl::GetIndexImpl<O, T...>(0) == Index;
	}

	template<class O>
	const O& Get() const
	{
#if WITH_EDITOR
		size_t index = Variant_Impl::GetIndexImpl<O, T...>(0);
		if (index != Index) {
			UE_LOG(LogSlow, Error, TEXT("TSlowVariant<T...>::Get(): Desired template parameter is not equals to value type."));
		}
#endif
		return *(const O*)Bytes;
	}

	template<class O>
	O& Get()
	{
		using Other = std::remove_reference_t<O>;

#if WITH_EDITOR
		size_t index = Variant_Impl::GetIndexImpl<O, T...>(0);
		if (index != Index) {
			UE_LOG(LogSlow, Error, TEXT("TSlowVariant<T...>::Get(): Desired template parameter is not equals to value type."));
		}
#endif
		return *(Other*)Bytes;
	}

	TSlowVariant& operator=(const TSlowVariant& InCopy)
	{
		if (InCopy.IsValid()) {
			if (Index == InCopy.Index) {
				Variant_Impl::Copy<T...>(Index, Bytes, InCopy.Bytes);
			}
			else {
				Variant_Impl::Destruct<T...>(Index, Bytes);
				Variant_Impl::CopyConstruct<T...>(InCopy.Index, Bytes, InCopy.Bytes);
				Index = InCopy.Index;
			}
		}
		else {
			if (IsValid()) {
				Variant_Impl::Destruct<T...>(Index, Bytes);
				Index = InvalidIndex;
			}
		}

		return *this;
	}

	TSlowVariant& operator=(TSlowVariant&& InMove)
	{
		if (InMove.IsValid()) {
			if (Index == InMove.Index) {
				Variant_Impl::Move<T...>(Index, Bytes, InMove.Bytes);
			}
			else {
				Variant_Impl::Destruct<T...>(Index, Bytes);
				Variant_Impl::MoveConstruct<T...>(InMove.Index, Bytes, InMove.Bytes);
				Index = InMove.Index;
			}
		}
		else {
			if (IsValid()) {
				Variant_Impl::Destruct<T...>(Index, Bytes);
				Index = InvalidIndex;
			}
		}

		return *this;
	}

	template<class O>
	TSlowVariant& operator=(const O& TCopy)
	{
		using Other = std::remove_reference_t<O>;

		size_t targetIndex = Variant_Impl::GetIndexImpl<O>(0);

		if (targetIndex == Index) {
			*(O*)Bytes = TCopy;
		}
		else {
			if (IsValid()) {
				Variant_Impl::Destruct<T...>(Index, Bytes);
			}

			new(Bytes) Other(TCopy);
			Index = targetIndex;
		}

		return *this;
	}

	template<class O>
	TSlowVariant& operator=(O&& TMove)
	{
		using Other = std::remove_reference_t<O>;

		size_t targetIndex = Variant_Impl::GetIndexImpl<Other, T...>(0);

		if (targetIndex == Index) {
			*(Other*)Bytes = MoveTemp(TMove);
		}
		else {
			if (IsValid()) {
				Variant_Impl::Destruct<T...>(Index, Bytes);
			}

			new(Bytes) Other(MoveTemp(TMove));
			Index = targetIndex;
		}

		return *this;
	}
};