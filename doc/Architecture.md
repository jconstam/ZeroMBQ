# Architecture {#Architecture}
## Data Flow
### ZMQ Receive -> Data Store
1. ZeroMQ message is published, the bridge ZMQSub task is subscribed to the tag
2. The tag is looked up in the tag dictionary
3. If the tag is found, the associated conversion method and destination array/register list (calculated or explicit? see discussion) is used to apply the values to the modbus array(s)

### Stored Data -> Modbus Read
1. Modbus read request is recieved
1. Look up the map that is associated with the given ID (with a hook to pass for external handling)
2. Check that the read is valid
3. Generate response, copy out values directly from the specified array

### Modbus Write -> Stored Data & ZMQ Send
1. Modbus write request is recieved
2. Look up the map that is associated with the given ID (with a hook to pass for external handling)
3. Check that the write is valid (all registers must pass before writing)
4. Update all values in the array
5. Somehow determine which tags are affected and Publish ZMQ message(s) for the changes (here be dragons) 
see discussion...


## Conversion 
Any data conversion for endianness/float swapping shall be handled before writing to the array.  

## Initialization
1. Modbus access is blocked
1. All registers are initialized to zero
2. User defined initialization values are applied (by ZeroMQ or other means?)
2. A configuration done signal (specific ZeroMQ message?) is sent
2. Modbus access is unblocked

## Configuration
1. configure
2. profit
3. ???
4. ^^wrong order?

## Discussion
Should allow calculating register number based on tag name or must have full 1->1 mapping for each tag/register?

Downside is a change of float swapping configuration will require a reinit: all float data currenlty in the map invalid.
Could force 'swap' handling to exist at conversion function level -> no longer a property of a map itself but of the conversion definition for registers in that map.

For write, an alternative to the above is not updating the array directly but publishing messages for each write and expecting the user system to re-publish updated register values on different tag names which are updated using the above method.  Could also support a hybrid.
