/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2009 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_RANGE_BT_MESSAGE_H_
#define _D_RANGE_BT_MESSAGE_H_

#include "SimpleBtMessage.h"
#include "PeerMessageUtil.h"

namespace aria2 {

class RangeBtMessage : public SimpleBtMessage {
private:
  size_t _index;
  uint32_t _begin;
  size_t _length;
  unsigned char* _msg;

  static const size_t MESSAGE_LENGTH = 17;
protected:
  template<typename T>
  static SharedHandle<T> create
  (const unsigned char* data, size_t dataLength)
  {
    PeerMessageUtil::assertPayloadLengthEqual(13, dataLength, T::NAME);
    PeerMessageUtil::assertID(T::ID, data, T::NAME);
    SharedHandle<T> message(new T());
    message->setIndex(PeerMessageUtil::getIntParam(data, 1));
    message->setBegin(PeerMessageUtil::getIntParam(data, 5));
    message->setLength(PeerMessageUtil::getIntParam(data, 9));
    return message;
  }
public:
  RangeBtMessage(uint8_t id, const std::string& name,
		 size_t index, uint32_t begin, size_t length);

  virtual ~RangeBtMessage();

  size_t getIndex() const { return _index; }

  void setIndex(size_t index) { _index = index; }

  uint32_t getBegin() const { return _begin; }

  void setBegin(uint32_t begin) { _begin = begin; }

  size_t getLength() const { return _length; }

  void setLength(size_t length) { _length = length; }

  virtual const unsigned char* getMessage();

  virtual size_t getMessageLength();

  virtual std::string toString() const;
};

} // namespace aria2

#endif // _D_RANGE_BT_MESSAGE_H_
