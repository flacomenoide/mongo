/**
 *    Copyright (C) 2014 MongoDB Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include "mongo/platform/basic.h"

#include "mongo/db/repl/operation_context_repl_mock.h"

#include "mongo/db/concurrency/lock_state.h"
#include "mongo/db/concurrency/locker.h"

namespace mongo {
namespace repl {

    OperationContextReplMock::OperationContextReplMock():
            _lockState(new MMAPV1LockerImpl()),
            _opID(0),
            _checkForInterruptStatus(Status::OK()),
            _maxTimeMicrosRemaining(0) {
    }

    OperationContextReplMock::~OperationContextReplMock() {}

    Locker* OperationContextReplMock::lockState() const {
        return _lockState.get();
    }

    unsigned int OperationContextReplMock::getOpID() const {
        return _opID;
    }

    void OperationContextReplMock::setOpID(unsigned int opID) {
        _opID = opID;
    }

    void OperationContextReplMock::checkForInterrupt() const {
        uassertStatusOK(checkForInterruptNoAssert());
    }

    Status OperationContextReplMock::checkForInterruptNoAssert() const {
        if (!_checkForInterruptStatus.isOK()) {
            return _checkForInterruptStatus;
        }

        return Status::OK();
    }

    void OperationContextReplMock::setCheckForInterruptStatus(Status status) {
        _checkForInterruptStatus = std::move(status);
    }

    uint64_t OperationContextReplMock::getRemainingMaxTimeMicros() const {
        return _maxTimeMicrosRemaining;
    }

    void OperationContextReplMock::setRemainingMaxTimeMicros(uint64_t micros) {
        _maxTimeMicrosRemaining = micros;
    }

}  // namespace repl
}  // namespace mongo
