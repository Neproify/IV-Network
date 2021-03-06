/*
* Copyright C GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef eIVGame_h
#define eIVGame_h

#define TASK_SIMPLE_MOVE_PLAYER 2
#define TASK_COMPLEX_PLAYER_ON_FOOT 4
#define TASK_COMPLEX_PLAYER_GUN 6
#define TASK_COMPLEX_PLAYER_PLACE_CAR_BOMB 7
#define TASK_COMPLEX_PLAYER_IDLES 8
#define TASK_COMPLEX_MEDIC_TREAT_INJURED_PED 100
#define TASK_COMPLEX_DRIVE_FIRE_TRUCK 107
#define TASK_COMPLEX_MEDIC_DRIVER 112
#define TASK_COMPLEX_MEDIC_PASSENGER 113
#define TASK_COMPLEX_PLAYER_SETTINGS_TASK 115
#define TASK_SIMPLE_STAND_STILL 203
#define TASK_SIMPLE_GET_UP 205
#define TASK_COMPLEX_GET_UP_AND_STAND_STILL 206
#define TASK_SIMPLE_FALL 207
#define TASK_COMPLEX_FALL_AND_GET_UP 208
#define TASK_SIMPLE_JUMP_LAUNCH 210
#define TASK_COMPLEX_JUMP 211
#define TASK_COMPLEX_DIE 217
#define TASK_SIMPLE_DEAD 218
#define TASK_SIMPLE_TIRED 219
#define TASK_COMPLEX_SIT_IDLE 221
#define TASK_COMPLEX_SIT_DOWN_THEN_IDLE_THEN_STAND_UP 223
#define TASK_COMPLEX_HIT_RESPONSE 230
#define TASK_SIMPLE_JUMP_IN_AIR 241
#define TASK_SIMPLE_JUMP_LAND 242
#define TASK_COMPLEX_SEQUENCE 244
#define TASK_COMPLEX_ON_FIRE 250
#define TASK_SIMPLE_CLIMB 254
#define TASK_COMPLEX_IN_WATER 268
#define TASK_SIMPLE_TRIGGER_LOOK_AT 269
#define TASK_COMPLEX_INJURED_ON_GROUND 278
#define TASK_SIMPLE_DO_NOTHING 281
#define TASK_SIMPLE_MOVE_DO_NOTHING 283
#define TASK_COMPLEX_CONTROL_MOVEMENT 285
#define TASK_COMPLEX_MOVE_SEQUENCE 286
#define TASK_COMPLEX_CLIMB_LADDER 287
#define TASK_COMPLEX_CLIMB_LADDER_FULLY 289
#define TASK_COMPLEX_MOVE_AROUND_COVER_POINTS 290
#define TASK_SIMPLE_PLAY_RANDOM_AMBIENTS 291
#define TASK_SIMPLE_MOVE_IN_AIR 293
#define TASK_COMPLEX_PICK_UP_OBJECT 314
#define TASK_COMPLEX_PICK_UP_AND_CARRY_OBJECT 315
#define TASK_SIMPLE_OPEN_DOOR 317
#define TASK_SIMPLE_SWAP_WEAPON 319
#define TASK_COMPLEX_SHOCKING_EVENT_WATCH 321
#define TASK_COMPLEX_SHOCKING_EVENT_FLEE 322
#define TASK_COMPLEX_SHOCKING_EVENT_GOTO 323
#define TASK_COMPLEX_SHOCKING_EVENT_HURRY_AWAY 324
#define TASK_SIMPLE_PUT_ON_HELMET 325
#define TASK_SIMPLE_TAKE_OFF_HELMET 326
#define TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION 327
#define TASK_COMPLEX_REACT_TO_PED_RAN_OVER 328
#define TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION_GET_OUT 329
#define TASK_COMPLEX_STATIONARY_SCENARIO 350
#define TASK_COMPLEX_SEATED_SCENARIO 351
#define TASK_COMPLEX_DRIVING_SCENARIO 353
#define TASK_COMPLEX_MOVE_BETWEEN_POINTS_SCENARIO 354
#define TASK_COMPLEX_CHAT_SCENARIO 355
#define TASK_COMPLEX_DRIVE_WANDER_FOR_TIME 359
#define TASK_COMPLEX_GET_IN_CAR_SCENARIO 361
#define TASK_COMPLEX_MOBILE_CHAT_SCENARIO 363
#define TASK_COMPLEX_POLICE_SNIPER_SCENARIO 365
#define TASK_COMPLEX_MOBILE_MAKE_CALL 366
#define TASK_COMPLEX_MELEE 431
#define TASK_SIMPLE_MOVE_MELEE_MOVEMENT 432
#define TASK_SIMPLE_MELEE_ACTION_RESULT 433
#define TASK_COMPLEX_EVASIVE_STEP 502
#define TASK_COMPLEX_MOVE_STEP_AWAY_FROM_COLLISION_OBJECTS 516
#define TASK_COMPLEX_WALK_ROUND_ENTITY 517
#define TASK_COMPLEX_LEAVE_CAR_AND_WANDER 572
#define TASK_COMPLEX_INVESTIGATE_DEAD_PED 600
#define TASK_COMPLEX_REACT_TO_GUN_AIMED_AT 601
#define TASK_COMPLEX_EXTINGUISH_FIRES 604
#define TASK_COMPLEX_AVOID_PLAYER_TARGETTING 605
#define TASK_COMPLEX_STEAL_CAR 702
#define TASK_COMPLEX_LEAVE_CAR_AND_FLEE 706
#define TASK_COMPLEX_SCREAM_IN_CAR_THEN_LEAVE 708
#define TASK_COMPLEX_CAR_DRIVE_BASIC 709
#define TASK_COMPLEX_DRIVE_TO_POINT 710
#define TASK_COMPLEX_CAR_DRIVE_WANDER 711
#define TASK_COMPLEX_LEAVE_ANY_CAR 714
#define TASK_COMPLEX_GET_OFF_BOAT 716
#define TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER 717
#define TASK_COMPLEX_CAR_DRIVE_TIMED 719
#define TASK_COMPLEX_DRIVE_POINT_ROUTE 721
#define TASK_COMPLEX_CAR_SET_TEMP_ACTION 723
#define TASK_COMPLEX_CAR_DRIVE_MISSION 724
#define TASK_COMPLEX_CAR_DRIVE 725
#define TASK_COMPLEX_CAR_DRIVE_MISSION_FLEE_SCENE 726
#define TASK_COMPLEX_CAR_DRIVE_MISSION_KILLED_PED 729
#define TASK_COMPLEX_PLAYER_DRIVE 732
#define TASK_COMPLEX_NEW_GET_IN_VEHICLE 734
#define TASK_COMPLEX_OPEN_VEHICLE_DOOR 735
#define TASK_COMPLEX_CLIMB_INTO_VEHICLE 736
#define TASK_COMPLEX_CLEAR_VEHICLE_SEAT 737
#define TASK_COMPLEX_NEW_EXIT_VEHICLE 738
#define TASK_COMPLEX_SHUFFLE_BETWEEN_SEATS 739
#define TASK_COMPLEX_GANG_DRIVEBY 740
#define TASK_COMPLEX_CLOSE_VEHICLE_DOOR 741
#define TASK_COMPLEX_BACK_OFF 742
#define TASK_COMPLEX_BE_ARRESTED_AND_DRIVEN_AWAY 743
#define TASK_COMPLEX_ARRESTED_AI_PED_AND_DRIVE_AWAY 744
#define TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL 800
#define TASK_SIMPLE_CAR_ALIGN 801
#define TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE 802
#define TASK_SIMPLE_CAR_OPEN_LOCKED_DOOR_FROM_OUTSIDE 803
#define TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE 805
#define TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_OUTSIDE 806
#define TASK_SIMPLE_CAR_GET_IN 807
#define TASK_SIMPLE_CAR_SHUFFLE 808
#define TASK_SIMPLE_CAR_SET_PED_IN_VEHICLE 811
#define TASK_SIMPLE_CAR_GET_OUT 813
#define TASK_SIMPLE_CAR_JUMP_OUT 814
#define TASK_SIMPLE_CAR_SET_PED_OUT 816
#define TASK_SIMPLE_CAR_SLOW_DRAG_OUT_PED 820
#define TASK_SIMPLE_CAR_SLOW_BE_DRAGGED_OUT 821
#define TASK_SIMPLE_SET_PED_AS_AUTO_DRIVER 827
#define TASK_SIMPLE_WAIT_UNTIL_PED_IS_OUT_OF_CAR 829
#define TASK_SIMPLE_CREATE_CAR_AND_GET_IN 832
#define TASK_SIMPLE_START_CAR 835
#define TASK_SIMPLE_SHUNT 836
#define TASK_SIMPLE_SMASH_CAR_WINDOW 838
#define TASK_SIMPLE_MOVE_GO_TO_POINT 900
#define TASK_COMPLEX_GO_TO_POINT_SHOOTING 901
#define TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL 903
#define TASK_COMPLEX_MOVE_FOLLOW_POINT_ROUTE 905
#define TASK_COMPLEX_MOVE_SEEK_ENTITY 907
#define TASK_COMPLEX_SMART_FLEE_POINT 910
#define TASK_COMPLEX_SMART_FLEE_ENTITY 911
#define TASK_COMPLEX_FOLLOW_LEADER_IN_FORMATION 913
#define TASK_COMPLEX_GO_TO_ATTRACTOR 915
#define TASK_COMPLEX_MOVE_AVOID_OTHER_PED_WHILE_WONDERING 917
#define TASK_COMPLEX_GO_TO_POINT_ANY_MEANS 918
#define TASK_COMPLEX_SEEK_ENTITY_ANY_MEANS 922
#define TASK_COMPLEX_FOLLOW_LEADER_ANY_MEANS 923
#define TASK_COMPLEX_GO_TO_POINT_AIMING 924
#define TASK_COMPLEX_FLEE_ANY_MEANS 927
#define TASK_COMPLEX_FLEE_SHOOTING 928
#define TASK_COMPLEX_FOLLOW_PATROL_ROUTE 931
#define TASK_COMPLEX_SEEK_ENTITY_AIMING 933
#define TASK_COMPLEX_FOLLOW_PED_FOOTSTEPS 936
#define TASK_COMPLEX_MOVE_FOLLOW_NAV_MESH_ROUTE 942
#define TASK_SIMPLE_MOVE_GO_TO_POINT_ON_ROUTE 943
#define TASK_COMPLEX_ESCAPE_BLAST 944
#define TASK_COMPLEX_MOVE_GET_TO_POINT_CONTINUOUS 945
#define TASK_COMPLEX_COP 946
#define TASK_COMPLEX_SEARCH_FOR_PED_ON_FOOT 947
#define TASK_COMPLEX_SEARCH_FOR_PED_IN_CAR 948
#define TASK_COMPLEX_MOVE_WANDER 949
#define TASK_COMPLEX_MOVE_BE_IN_FORMATION 950
#define TASK_COMPLEX_MOVE_CROWD_AROUND_LOCATION 951
#define TASK_COMPLEX_MOVE_CROSS_ROAD_AT_TRAFFIC_LIGHTS 952
#define TASK_COMPLEX_MOVE_WAIT_FOR_TRAFFIC 953
#define TASK_COMPLEX_MOVE_GO_TO_POINT_STAND_STILL_ACHIVE_HEADING 955
#define TASK_COMPLEX_MOVE_RETURN_TO_ROUTE 958
#define TASK_COMPLEX_MOVE_GO_TO_SHELTER_AND_WAIT 959
#define TASK_COMPLEX_MOVE_GET_ON_TO_MAIN_NAV_MESH 960
#define TASK_COMPLEX_MOVE_GO_TO_POINT_RELATIVE_TO_ENTITY_AND_STAND_STILL 962
#define TASK_COMPLEX_COP_HELICOPTOR 963
#define TASK_COMPLEX_HELICOPTOR_STRAFE 964
#define TASK_COMPLEX_FLEE_AND_DRIVE 966
#define TASK_COMPLEX_GET_OUT_OF_WATER 967
#define TASK_COMPLEX_DESTROY_CAR 1003
#define TASK_COMPLEX_DESTROY_CAR_ARMED 1005
#define TASK_SIMPLE_THROW_PROJECTILE 1018
#define TASK_COMPLEX_SEEK_COVER 1036
#define TASK_COMPLEX_AIM_AND_THROW_PROJECTILE 1038
#define TASK_SIMPLE_PLAYER_AIM_PROJECTILE 1039
#define TASK_COMPLEX_GUN 1040
#define TASK_SIMPLE_AIM_GUN 1041
#define TASK_SIMPLE_FIRE_GUN 1042
#define TASK_SIMPLE_RELOAD_GUN 1043
#define TASK_COMPLEX_SLIDE_INTO_COVER 1044
#define TASK_COMPLEX_PLAYER_IN_COVER 1046
#define TASK_COMPLEX_GO_INTO_COVER 1047
#define TASK_COMPLEX_COMBAT_CLOSEST_TARGET_IN_AREA 1048
#define TASK_SIMPLE_NEW_GANG_DRIVE_BY 1049
#define TASK_COMPLEX_COMBAT_ADDITIONAL_TASK 1050
#define TASK_COMPLEX_NEW_USE_COVER 1054
#define TASK_COMPLEX_THROW_PROJECTILE 1058
#define TASK_COMPLEX_ARREST_PED 1101
#define TASK_COMPLEX_GANG_HASSLE_PED 1212
#define TASK_SIMPLE_MOVE_SWIM 1304
#define TASK_COMPLEX_MOVE_ABOUT_INJURED 1310
#define TASK_COMPLEX_REVIVE 1311
#define TASK_COMPLEX_REACT 1312
#define TASK_COMPLEX_COMBAT 1900
#define TASK_COMPLEX_COMBAT_FIRE_SUBTASK 1901
#define TASK_COMPLEX_COMBAT_ADVANCE_SUBTASK 1902
#define TASK_COMPLEX_COMBAT_SEEK_COVER_SUBTASK 1903
#define TASK_COMPLEX_COMBAT_RETREAT_SUBTASK 1904
#define TASK_COMPLEX_COMBAT_CHARGE_SUBTASK 1905
#define TASK_COMPLEX_COMBAT_INVESTIGATE_SUBTASK 1906
#define TASK_COMPLEX_COMBAT_PULL_FROM_CAR_SUBTASK 1907
#define TASK_COMPLEX_COMBAT_PERSUE_IN_CAR_SUBTASK 1908
#define TASK_COMPLEX_COMBAT_BUST_PED 1910
#define TASK_COMPLEX_COMBAT_EXECUTE_PED_SUBTASK 1911
#define TASK_COMPLEX_COMBAT_FLANK_SUBTASK 1913
#define TASK_COMPLEX_SET_AND_GUARD_AREA 1932
#define TASK_COMPLEX_STAND_GUARD 1933
#define TASK_COMPLEX_SEPERATE 1934
#define TASK_SIMPLE_NM_RELAX 2104
#define TASK_SIMPLE_NM_POSE 2105
#define TASK_SIMPLE_NM_BRACE 2106
#define TASK_SIMPLE_NM_SHOT 2107
#define TASK_SIMPLE_NM_HIGH_FALL 2108
#define TASK_SIMPLE_NM_BALANCE 2109
#define TASK_SIMPLE_NM_EXPLOSION 2110
#define TASK_SIMPLE_NM_ON_FIRE 2111
#define TASK_SIMPLE_NM_SCRIPT_CONTROL 2112
#define TASK_SIMPLE_NM_JUMP_ROLL_FROM_ROAD_VEHICLE 2113
#define TASK_SIMPLE_NM_SIT 2115
#define TASK_SIMPLE_BLEND_FROM_NM 2117
#define TASK_COMPLEX_NM 2118
#define TASK_TYPE_NONE 9999

#endif // eIVGame_h