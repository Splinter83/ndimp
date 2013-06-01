#ifndef _GENERIC_MESSAGE_HANDLER_H_
#define _GENERIC_MESSAGE_HANDLER_H_

#include "TypeList.h"
#include "MultipleInterface.h"
#include "InterfaceImplementation.h"
#include "CircularBuffer.h"
#include "IGenericMessageHandler.h"
#include "Endianess.h"

#include "GenericEventListener.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

template<class T> class SendIfElement {
public:
	virtual ~SendIfElement() {
	}
	virtual int Send(const T & msg)=0;
};

template<typename OutTL> class SendInterface: public MultipleInterface<
		SendIfElement, OutTL> {
public:
	virtual ~SendInterface() {
	}

	template<typename H> int Send(const H & msg) {
		return (static_cast<SendIfElement<H> *>(this))->Send(msg);
	}
};

template<typename HeaderTypeTrait, typename OutTL,
		template<typename, typename > class LengthCalculationPolicy>
class GenericSenderBase: public SendInterface<OutTL> {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

protected:
	IOutputDataStream * _OutputStream;
	LenType HeaderType::* _AttrPtrLen;
	IDType HeaderType::* _AttrPtrID;

public:
	typedef LenType HeaderType::* AttrPtrLen; // LenType HeaderType::*

public:
	virtual ~GenericSenderBase() {
	}
protected:

	GenericSenderBase() {
	}

	int SendMessage(const HeaderType & header) {
		int byteWritten = 0;
		// LCP_Default<HeaderType, LenType, OutTL>::CalculateLen(header, _AttrPtrLen);
		int len =
				(int) LengthCalculationPolicy<HeaderTypeTrait, OutTL>::CalculateLen(
						header, _AttrPtrID, _AttrPtrLen);
		if (len) {
			if (_OutputStream) {
				byteWritten = _OutputStream->Write(
						reinterpret_cast<const char *>(&header), len);
			} else {
				std::cout << "Message Sending aborted" << std::endl;

			}
		} else {
			std::cout << "Can't recognize the message" << std::endl;
		}
		return byteWritten;
	}

	void SetOutputDataStream(IOutputDataStream * ods) {
		_OutputStream = ods;
	}

};

template<typename T, typename Base> class SendElement: public Base {
public:

	typedef typename Base::HeaderType HeaderType;
	virtual ~SendElement() {
	}

	SendElement() {
	}

	int Send(const T & msg) {
		return Base::SendMessage(reinterpret_cast<const HeaderType &>(msg));
	}

	template<typename H> inline int Send(const H & msg) {
		return Base::Send(msg);
	}
};

template<typename OutTL, typename HeaderTypeTrait,
		template<typename, typename > class LengthCalculationPolicy>
class GenericSender: public InterfaceImplementation<SendElement, OutTL,
		GenericSenderBase<HeaderTypeTrait, OutTL, LengthCalculationPolicy> > {
public:
	typedef InterfaceImplementation<SendElement, OutTL,
			GenericSenderBase<HeaderTypeTrait, OutTL, LengthCalculationPolicy> > Base;

	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	GenericSender(IDType HeaderType::* attr_ptr_id,
			LenType HeaderType::* attr_ptr_len, IOutputDataStream * s) {
		Base::_OutputStream = s;
		Base::_AttrPtrLen = attr_ptr_len;
		Base::_AttrPtrID = attr_ptr_id;
	}

	virtual ~GenericSender() {
	}

	void SetOutputDataStream(IOutputDataStream * ods) {
		Base::SetOutputDataStream(ods);
	}

};

template<typename HeaderTypeTrait, typename InTL,
		template<typename > class IDComparisonPolicy> class GenericReceiverBase: public IMultipleNotifier<
		InTL> {

public:

	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	typedef IDType HeaderType::* AttrPtrID;
	typedef LenType HeaderType::* AttrPtrLen;

	typedef IDComparisonPolicy<HeaderTypeTrait> BaseIDComparisonPolicy;

protected:

	AttrPtrID _AttrPtrID;
	AttrPtrLen _AttrPtrLen;

public:

	virtual ~GenericReceiverBase() {
	}

protected:

	GenericReceiverBase() {
	}

	inline void HandleMessage(const HeaderType & header) {
	}

	template<typename H> inline void AddListener(IListener<H> * listener) {
	}

	template<typename H> inline void RemoveListener(IListener<H> * listener) {
	}

	template<typename H> inline void NotifyListeners(const H & msg) {
	}

};

template<typename T, class Base> class GenericReceiverElement: public Base {

public:

	typedef typename Base::HeaderType HeaderType;
	typedef typename Base::AttrPtrID AttrPtrID;
	typedef typename Base::AttrPtrLen AttrPtrLen;

	typedef typename Base::BaseIDComparisonPolicy BaseIDComparisonPolicy;

	virtual ~GenericReceiverElement() {
	}

	inline void HandleMessage(const HeaderType & header) {
		// size   ->     header.*AttrPtrLen
		// id     ->     header.*AttrPtrID

		typename Base::AttrPtrID tmp_ptr = Base::_AttrPtrID;
		typename Base::AttrPtrLen tmp_len = Base::_AttrPtrLen;

		if (BaseIDComparisonPolicy::DoesIDMatch(header, tmp_ptr, tmp_len,
				T::MsgID)) {
			NotifyListeners(reinterpret_cast<const T &>(header));
		} else {
			Base::HandleMessage(header);
		}
	}

	void AddListener(IListener<T> * listener) {
		_Notifier.AddListener(listener);
	}

	void RemoveListener(IListener<T> * listener) {
		_Notifier.RemoveListener(listener);
	}

	template<typename H> inline void AddListener(IListener<H> * listener) {
		Base::AddListener(listener);
	}

	template<typename H> inline void RemoveListener(IListener<H> * listener) {
		Base::RemoveListener(listener);
	}

protected:

	void NotifyListeners(const T & msg) {
		_Notifier.NotifyListeners(msg);
	}

	template<typename H> inline void NotifyListeners(const H & msg) {
		Base::NotifyListeners(msg);
	}

private:

	GenericNotifier<T> _Notifier;
};

template<typename HeaderTypeTrait> class ICP_Default {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static bool DoesIDMatch(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr,
			IDType id) {
		return (header.*id_ptr == id);
	}
};

template<typename HeaderTypeTrait> class ICP_LE2BE {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static bool DoesIDMatch(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr,
			IDType id) {
		IDType a;
		a = header.*id_ptr;
		normalyzeEndianess(a);

		return (a == id);
		//return (header.*id_ptr == id);
	}
};

template<typename InTL, typename HeaderTypeTrait,
		template<typename > class IDComparisonPolicy = ICP_LE2BE>
class GenericReceiver: public InterfaceImplementation<GenericReceiverElement,
		InTL, GenericReceiverBase<HeaderTypeTrait, InTL, IDComparisonPolicy> > {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::IDType IDType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef IDType HeaderType::* AttrPtrID;
	typedef LenType HeaderType::* AttrPtrLen;

	GenericReceiver(AttrPtrID attr_ptr_id, AttrPtrLen attr_ptr_len) {
		InterfaceImplementation < GenericReceiverElement, InTL, GenericReceiverBase<
				HeaderTypeTrait, InTL, IDComparisonPolicy> > ::_AttrPtrID =
				attr_ptr_id;

		InterfaceImplementation < GenericReceiverElement, InTL, GenericReceiverBase<
				HeaderTypeTrait, InTL, IDComparisonPolicy> > ::_AttrPtrLen =
				attr_ptr_len;

	}
	;

	virtual ~GenericReceiver() {
	}

};

template<typename HeaderTypeTrait, typename TL> class LCP_Offset {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return (header.*len_ptr + 4);
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

template<typename HeaderTypeTrait, typename TL> class LCP_Offset2 {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return (header.*len_ptr + 2);
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

template<typename HeaderTypeTrait, typename TL> class LCP_Offset4 {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return (header.*len_ptr + 4);
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

//serve nel caso del PPI
template<typename HeaderTypeTrait, typename TL> class LCP_Offset8 {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return (header.*len_ptr + 8);
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

template<typename HeaderTypeTrait, typename TL> class LCP_Default {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return header.*len_ptr;
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

template<typename HeaderTypeTrait, typename TL> class LCP_NoLenField {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return (header.*len_ptr + sizeof(LenType));
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

//implementazione della len policy per sistemi LE che inviano a sistemi BE
template<typename HeaderTypeTrait, typename TL> class LCP_Offset2_LE2BE {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		LenType a;
		a = header.*len_ptr;
		normalyzeEndianess(a);
		a += 2;

		return a;
		//return header.*len_ptr;
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

//implementazione della len policy per sistemi LE che inviano a sistemi BE
//utilizzato Offset 4 per gli header con lenght = 4
template<typename HeaderTypeTrait, typename TL> class LCP_Offset4_LE2BE {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		LenType a;
		a = header.*len_ptr;
		normalyzeEndianess(a);
		a += 4;

		return a;
		//return header.*len_ptr;
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		return sizeof(HeaderType);
	}
};

template<typename T> class MessageLenCalculator {
public:
	static int GetSize(const T & msg) {
		return sizeof(T);
	}

	static int GetMinimumNeededSize(const T & msg) {
		return sizeof(T);
	}
};

template<typename HeaderTypeTrait, typename TL> class LCP_FixedSize {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	typedef typename TL::head Head;
	typedef typename TL::tail Tail;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		if (header.*id_ptr == Head::MsgID) {
			return MessageLenCalculator<Head>::GetSize(
					reinterpret_cast<const Head &>(header));
		} else
			return LCP_FixedSize<HeaderTypeTrait, Tail>::CalculateLen(header,
					id_ptr, len_ptr);
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		if (header.*id_ptr == Head::MsgID) {
			return MessageLenCalculator<Head>::GetMinimumNeededSize(
					reinterpret_cast<const Head &>(header));
		} else
			return LCP_FixedSize<HeaderTypeTrait, Tail>::CalculateMinimumNeededSize(
					header, id_ptr, len_ptr);

	}

};

template<typename HeaderTypeTrait> class LCP_FixedSize<HeaderTypeTrait, NullType> {
public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::LenType LenType;
	typedef typename HeaderTypeTrait::IDType IDType;

	static LenType CalculateLen(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		std::cout << "Message not identified" << std::endl;
		return 0;
	}

	static LenType CalculateMinimumNeededSize(const HeaderType & header,
			IDType HeaderType::* id_ptr, LenType HeaderType::* len_ptr) {
		std::cout << "Message not identified" << std::endl;
		return 0;
	}

};

template<typename InTL, typename OutTL, typename HeaderTypeTrait,
		int MaxMsgSize = 4096,
		template<typename, typename > class LengthCalculationPolicy = LCP_Default,
		template<typename > class IDComparisonPolicy = ICP_LE2BE>
class GenericMessageHandler: public GenericSender<OutTL, HeaderTypeTrait,
		LengthCalculationPolicy>, public GenericReceiver<InTL, HeaderTypeTrait,
		IDComparisonPolicy>,
//                             public LengthCalculationPolicy<HeaderTypeTrait,  InTL>,
		public IGenericMessageHandler {
private:
	CircularBuffer _CircularBuffer;
	char _MessageBuffer[MaxMsgSize];

public:
	typedef typename HeaderTypeTrait::HeaderType HeaderType;
	typedef typename HeaderTypeTrait::IDType IDType;
	typedef typename HeaderTypeTrait::LenType LenType;

	typedef IDType HeaderType::* AttrPtrID;
	typedef LenType HeaderType::* AttrPtrLen;

	GenericMessageHandler(AttrPtrID attr_ptr_id, AttrPtrLen attr_ptr_len,
			int buffer_size, IOutputDataStream * s = NULL) :
			GenericSender<OutTL, HeaderTypeTrait, LengthCalculationPolicy>(
					attr_ptr_id, attr_ptr_len, s), GenericReceiver<InTL,
					HeaderTypeTrait, IDComparisonPolicy>(attr_ptr_id,
					attr_ptr_len), _CircularBuffer(buffer_size) {
	}

	virtual ~GenericMessageHandler() {
	}

	void SetOutputDataStream(IOutputDataStream * ods) {
		//std::cout<<"GenericMessageHandler::SetOutputDataStream"<<std::endl;
		GenericSender<OutTL, HeaderTypeTrait, LengthCalculationPolicy>::SetOutputDataStream(
				ods);
	}

	int Write(const char * data, int size) {
		return ConsumeBuffer(data, size);
	}

private:
	int ConsumeBuffer(const char * data, int size) {
		int written_size = _CircularBuffer.Put(data, size);
		while (AnalyzeBuffer())
			;
		return written_size;
	}

	bool AnalyzeBuffer() {
		bool result = false;
		int read_header = _CircularBuffer.Read(_MessageBuffer, MaxMsgSize);
		if (0 <= read_header) {
			if ((unsigned long) read_header >= sizeof(HeaderType)) {
				HeaderType & header =
						reinterpret_cast<HeaderType &>(_MessageBuffer[0]);

				int minimum_needed_size = (int) LengthCalculationPolicy<
						HeaderTypeTrait, InTL>::CalculateMinimumNeededSize(
						header,
						GenericReceiver<InTL, HeaderTypeTrait,
								IDComparisonPolicy>::_AttrPtrID,
						GenericReceiver<InTL, HeaderTypeTrait,
								IDComparisonPolicy>::_AttrPtrLen);

				if (read_header >= minimum_needed_size) {
					int msg_len = (int) LengthCalculationPolicy<HeaderTypeTrait,
							InTL>::CalculateLen(header,
							GenericReceiver<InTL, HeaderTypeTrait,
									IDComparisonPolicy>::_AttrPtrID,
							GenericReceiver<InTL, HeaderTypeTrait,
									IDComparisonPolicy>::_AttrPtrLen);
					if (msg_len < 0)
						printf("ATTENZIONE!!!! Len[%d]\n", msg_len);
					if (msg_len > 0) {
						int read_message = _CircularBuffer.Read(_MessageBuffer,
								msg_len);
						if (read_message == msg_len) {
							_CircularBuffer.Consume(read_message);
							GenericReceiver<InTL, HeaderTypeTrait,
									IDComparisonPolicy>::HandleMessage(header);
							result = true;
						}
					} else
						_CircularBuffer.Reset();
				}
			}
		}
		return result;
	}

};

#endif
