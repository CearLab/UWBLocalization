/*==========================================================================*
 *==========================================================================*
 * Vicon provide the software below “as is," and you use the software at your
 * own risk. Vicon makes no warranties as to performance, merchantability, 
 * fitness for a particular purpose, or any other warranties whether expressed 
 * or implied. No oral or written communication from or information provided 
 * by Vicon shall create a warranty. Under no circumstances shall Vicon be 
 * liable for direct, indirect, special, incidental, or consequential damages 
 * resulting from the use, misuse, or inability to use this software, even if 
 * Vicon has been advised of the possibility of such damages.
 *==========================================================================*
 *==========================================================================*/

/*
 * Data Block Format
 *
 * All data blocks are sent with a HeaderObject followed by 1 or more Items.
 * Each item will consist of an ItemHeader followed by item specific information.
 * If the packet size specified is not large enough to accommodate all of the
 * items, multiple data blocks will be generated for the same frame.
 *
 * Example: 2 Tracker Objects
 * 
 * 0-3      Frame Number                nnnn
 * 4        ItemsInBlock                2
 * 5        ItemHeader:ItemID           0
 * 6-7      ItemHeader:ItemDataSize     72
 * 8-31     TrackerObject:ItemName      'O''b''j''e''c''t''1'00000000000000000
 * 32-39    TrackerObject:TransX
 * 40-47    TrackerObject:TransY
 * 48-55    TrackerObject:TransZ
 * 56-63    TrackerObject:RotX
 * 64-71    TrackerObject:RotY
 * 72-79    TrackerObject:RotZ
 * 80       ItemHeader:ItemID           0
 * 81-82    ItemHeader:ItemDataSize     72
 * 83-106   TrackerObject:ItemName      'O''b''j''e''c''t''2'00000000000000000
 * 107-114  TrackerObject:TransX
 * 115-122  TrackerObject:TransY
 * 123-130  TrackerObject:TransZ
 * 131-138  TrackerObject:RotX
 * 139-146  TrackerObject:RotY
 * 147-154  TrackerObject:RotZ
 */

  struct HeaderObject
  {
    uint32_T  FrameNumber;
    uint8_T   ItemsInBlock;
  };

  #define VICON_TRACKER_OBJECT_ITEM_ID   0
  
  struct ItemHeader
  {
    uint8_T     ItemID;
    uint16_T    ItemDataSize;
  };

  struct TrackerObject
  {
    uint8_T ItemName[24];
    double  TransX;
    double  TransY;
    double  TransZ;
    double  RotX;
    double  RotY;
    double  RotZ;
  };



