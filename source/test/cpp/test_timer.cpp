#include "rcore/c_timer.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(timer)
{
    UNITTEST_FIXTURE(clock_ops)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() { ntimer::default_clock_ops(); }

        struct test_clock_t
        {
            u64 m_millis;
            u64 m_micros;
        };

        static u64 test_millis(void* context) { return ((test_clock_t*)context)->m_millis; }
        static u64 test_micros(void* context) { return ((test_clock_t*)context)->m_micros; }

        UNITTEST_TEST(injected_clock)
        {
            test_clock_t        clock = {123456, 123456789};
            ntimer::set_clock_ops(&clock, test_millis, test_micros);

            CHECK_EQUAL(ntimer::millis(), clock.m_millis);
            CHECK_EQUAL(ntimer::micros(), clock.m_micros);

            clock.m_millis = 654321;
            clock.m_micros = 654321987;
            CHECK_EQUAL(ntimer::millis(), clock.m_millis);
            CHECK_EQUAL(ntimer::micros(), clock.m_micros);
        }

        UNITTEST_TEST(default_clock)
        {
            ntimer::default_clock_ops();

            CHECK_TRUE(ntimer::millis() > 0);
            CHECK_TRUE(ntimer::micros() > 0);
        }
    }
}
UNITTEST_SUITE_END