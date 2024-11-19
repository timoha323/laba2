#include "sharedPointer.h"
#include "functionalTests.h"
#include "uniquePointer.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include "memory"
#include "cassert"

std::string runUnqPtrTests() {
    std::ostringstream result;
    result << "UniquePtr Tests:\n";

    result << "  Functional Test 1 (add element): ";
    {
        UniquePtr<int> p1(new int(10));
        assert(*p1 == 10);
        result << "Passed" << '\n';
    }

    result << "  Functional Test 2 (release test): ";
    {
        UniquePtr<int> p1(new int(20));
        int *rawPtr = p1.release();
        assert(*rawPtr == 20);
        result << "Passed" << '\n';
        delete rawPtr;
    }
    return result.str();
}

std::string runShrdPtrTests() {
    std::ostringstream result;
    result << "SharedPointer Tests:\n";

    result << "  Functional Test 1 (shrd init): ";
    {
        SharedPointer<int> p1(new int(10));
        result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
    }

    result << "  Functional Test 2 (shrd release): ";
    {
        SharedPointer<int> p1(new int(10));
        result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
    }

    result << "  Functional Test 3 (shrd(other shared)): ";
    {
        SharedPointer<int> p1(new int(10));
        std::ostringstream preRes;
        preRes << '\n' << p1.getRefCount() << " - Referenc counter before copy\n";
        SharedPointer<int> p2(p1);
        preRes << '\n' << p1.getRefCount() << " - Referenc counter after copy\n";
        result << (*p2 == 10 && *p2 == 10 ? "Passed" : "Failed") << "\n";
        result << preRes.str() << "\n";
    }

    return result.str();
}