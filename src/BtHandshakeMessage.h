/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
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
#ifndef _D_BT_HANDSHAKE_MESSAGE_H_
#define _D_BT_HANDSHAKE_MESSAGE_H_

#include "SimpleBtMessage.h"

namespace aria2 {

class BtHandshakeMessage : public SimpleBtMessage {
public:
  static const size_t PSTR_LENGTH = 19;
  static const unsigned char* BT_PSTR;
  static const size_t RESERVED_LENGTH = 8;
  static const size_t MESSAGE_LENGTH = 68;
private:
  uint8_t pstrlen;
  unsigned char* pstr;
  unsigned char* reserved;
  unsigned char* infoHash;
  unsigned char* peerId;
  unsigned char* msg;
  void init();
public:
  BtHandshakeMessage();
  /**
   * infoHash must be 20 byte length.
   * peerId must be 20 byte length.
   */
  BtHandshakeMessage(const unsigned char* infoHash, const unsigned char* peerId);

  static SharedHandle<BtHandshakeMessage>
  create(const unsigned char* data, size_t dataLength);

  virtual ~BtHandshakeMessage() {
    delete [] msg;
    delete [] pstr;
    delete [] reserved;
    delete [] infoHash;
    delete [] peerId;
  }

  static const uint8_t ID = INT8_MAX;

  static const std::string NAME;

  virtual void doReceivedAction() {};

  virtual const unsigned char* getMessage();

  virtual size_t getMessageLength();

  virtual std::string toString() const;

  bool isFastExtensionSupported() const;

  bool isExtendedMessagingEnabled() const;

  bool isDHTEnabled() const;

  void setDHTEnabled(bool enabled)
  {
    if(enabled) {
      this->reserved[7] |= 0x01;
    } else {
      this->reserved[7] &= ~0x01;
    }
  }

  uint8_t getPstrlen() const {
    return pstrlen;
  }

  const unsigned char* getPstr() const {
    return pstr;
  }

  const unsigned char* getReserved() const {
    return reserved;
  }

  const unsigned char* getInfoHash() const {
    return infoHash;
  }

  void setInfoHash(const unsigned char* infoHash);

  const unsigned char* getPeerId() const {
    return peerId;
  }

  void setPeerId(const unsigned char* peerId);
};

} // namespace aria2

#endif // _D_HANDSHAKE_MESSAGE_H_
