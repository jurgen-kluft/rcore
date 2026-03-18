#include "rcore/c_target.h"
#include "ccore/c_allocator.h"
#include "rcore/c_packet.h"

#include "cunittest/cunittest.h"

using namespace ncore;
using namespace ncore::npacket;

UNITTEST_SUITE_BEGIN(packet)
{
    UNITTEST_FIXTURE(write)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

        UNITTEST_TEST(test)
        {
            packet_t packet;
            packet.begin();

            // Write sensor values
            npacket::sensor_block_t sensors;
            sensors.begin(&packet);
            sensors.write(&packet,  npacket::sensor_block_t::ID_TEMPERATURE, 25);
            sensors.write(&packet, npacket::sensor_block_t::ID_HUMIDITY, 60);

            // Finalize the packet
            CHECK_EQUAL(2, packet.finalize());

            // Check the size of the packet
            CHECK_EQUAL((packet_t::HeaderSize + 3 + 3), packet.Size);
        }
    }
}
UNITTEST_SUITE_END
