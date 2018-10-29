# Hardware Model Design

The design consists of several major components:
- *Release mechanism* - the top of the fountain, which includes the speaker and release nozzle where water exits the internal structure
- *Visual chamber* - consists of the open space, lined with LEDs on the side wall
- *Vascular system* - the system including the collection bucket, pump, and tubes which transport water from the bottom back to the top of the fountain
- *Brain* - the system of electronics, stored at the bottom of the fountain

## Release Mechanism

The release mechanism is a closed, internal chamber containing primarily the speaker, which creates the oscillatory output of the output water stream, connected to the exit end of the tube. The opening to release water should be at the bottom of the top chamber.

## Visual chambers

The visual chamber consists of LEDs along each side and a visible stream of water down the center. The chamber will be sealed off with transparent plastic on the front and back to prevent tampering with the water stream.

The sides of the visual chambers should contain the tube carrying water up to the top as well as the wires for the speaker.

## Vascular system

The vascular system should include the collection bucket, which collects the water and feeds back into the transport tube. The peristaltic pump should be stored in the bottom chamber and will be used to pump water back to the top.

## Brain

The system of electronics which powers the entire system. The bottom panel of the electronics should be easily removable from the rest of the system for easy electrical debugging, and an interface should exist to allow for new program loading (i.e. the micro USB interface should be accessible while the entire system is contained within the bottom chamber). There should also be an easy interface to provide power to the system.