/*
 * Copyright (c) 2016 QLogic Corporation.
 * All rights reserved.
 * www.qlogic.com
 *
 * See LICENSE.qede_pmd for copyright and licensing details.
 */

#ifndef __RT_DEFS_H__
#define __RT_DEFS_H__

/* Runtime array offsets */
#define DORQ_REG_PF_MAX_ICID_0_RT_OFFSET                            0
#define DORQ_REG_PF_MAX_ICID_1_RT_OFFSET                            1
#define DORQ_REG_PF_MAX_ICID_2_RT_OFFSET                            2
#define DORQ_REG_PF_MAX_ICID_3_RT_OFFSET                            3
#define DORQ_REG_PF_MAX_ICID_4_RT_OFFSET                            4
#define DORQ_REG_PF_MAX_ICID_5_RT_OFFSET                            5
#define DORQ_REG_PF_MAX_ICID_6_RT_OFFSET                            6
#define DORQ_REG_PF_MAX_ICID_7_RT_OFFSET                            7
#define DORQ_REG_VF_MAX_ICID_0_RT_OFFSET                            8
#define DORQ_REG_VF_MAX_ICID_1_RT_OFFSET                            9
#define DORQ_REG_VF_MAX_ICID_2_RT_OFFSET                            10
#define DORQ_REG_VF_MAX_ICID_3_RT_OFFSET                            11
#define DORQ_REG_VF_MAX_ICID_4_RT_OFFSET                            12
#define DORQ_REG_VF_MAX_ICID_5_RT_OFFSET                            13
#define DORQ_REG_VF_MAX_ICID_6_RT_OFFSET                            14
#define DORQ_REG_VF_MAX_ICID_7_RT_OFFSET                            15
#define DORQ_REG_PF_WAKE_ALL_RT_OFFSET                              16
#define DORQ_REG_TAG1_ETHERTYPE_RT_OFFSET                           17
#define IGU_REG_PF_CONFIGURATION_RT_OFFSET                          18
#define IGU_REG_VF_CONFIGURATION_RT_OFFSET                          19
#define IGU_REG_ATTN_MSG_ADDR_L_RT_OFFSET                           20
#define IGU_REG_ATTN_MSG_ADDR_H_RT_OFFSET                           21
#define IGU_REG_LEADING_EDGE_LATCH_RT_OFFSET                        22
#define IGU_REG_TRAILING_EDGE_LATCH_RT_OFFSET                       23
#define CAU_REG_CQE_AGG_UNIT_SIZE_RT_OFFSET                         24
#define CAU_REG_SB_VAR_MEMORY_RT_OFFSET                             761
#define CAU_REG_SB_VAR_MEMORY_RT_SIZE                               736
#define CAU_REG_SB_VAR_MEMORY_RT_OFFSET                             761
#define CAU_REG_SB_VAR_MEMORY_RT_SIZE                               736
#define CAU_REG_SB_ADDR_MEMORY_RT_OFFSET                            1497
#define CAU_REG_SB_ADDR_MEMORY_RT_SIZE                              736
#define CAU_REG_PI_MEMORY_RT_OFFSET                                 2233
#define CAU_REG_PI_MEMORY_RT_SIZE                                   4416
#define PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET                6649
#define PRS_REG_TASK_ID_MAX_INITIATOR_PF_RT_OFFSET                  6650
#define PRS_REG_TASK_ID_MAX_INITIATOR_VF_RT_OFFSET                  6651
#define PRS_REG_TASK_ID_MAX_TARGET_PF_RT_OFFSET                     6652
#define PRS_REG_TASK_ID_MAX_TARGET_VF_RT_OFFSET                     6653
#define PRS_REG_SEARCH_TCP_RT_OFFSET                                6654
#define PRS_REG_SEARCH_FCOE_RT_OFFSET                               6655
#define PRS_REG_SEARCH_ROCE_RT_OFFSET                               6656
#define PRS_REG_ROCE_DEST_QP_MAX_VF_RT_OFFSET                       6657
#define PRS_REG_ROCE_DEST_QP_MAX_PF_RT_OFFSET                       6658
#define PRS_REG_SEARCH_OPENFLOW_RT_OFFSET                           6659
#define PRS_REG_SEARCH_NON_IP_AS_OPENFLOW_RT_OFFSET                 6660
#define PRS_REG_OPENFLOW_SUPPORT_ONLY_KNOWN_OVER_IP_RT_OFFSET       6661
#define PRS_REG_OPENFLOW_SEARCH_KEY_MASK_RT_OFFSET                  6662
#define PRS_REG_TAG_ETHERTYPE_0_RT_OFFSET                           6663
#define PRS_REG_LIGHT_L2_ETHERTYPE_EN_RT_OFFSET                     6664
#define SRC_REG_FIRSTFREE_RT_OFFSET                                 6665
#define SRC_REG_FIRSTFREE_RT_SIZE                                   2
#define SRC_REG_LASTFREE_RT_OFFSET                                  6667
#define SRC_REG_LASTFREE_RT_SIZE                                    2
#define SRC_REG_COUNTFREE_RT_OFFSET                                 6669
#define SRC_REG_NUMBER_HASH_BITS_RT_OFFSET                          6670
#define PSWRQ2_REG_CDUT_P_SIZE_RT_OFFSET                            6671
#define PSWRQ2_REG_CDUC_P_SIZE_RT_OFFSET                            6672
#define PSWRQ2_REG_TM_P_SIZE_RT_OFFSET                              6673
#define PSWRQ2_REG_QM_P_SIZE_RT_OFFSET                              6674
#define PSWRQ2_REG_SRC_P_SIZE_RT_OFFSET                             6675
#define PSWRQ2_REG_TSDM_P_SIZE_RT_OFFSET                            6676
#define PSWRQ2_REG_TM_FIRST_ILT_RT_OFFSET                           6677
#define PSWRQ2_REG_TM_LAST_ILT_RT_OFFSET                            6678
#define PSWRQ2_REG_QM_FIRST_ILT_RT_OFFSET                           6679
#define PSWRQ2_REG_QM_LAST_ILT_RT_OFFSET                            6680
#define PSWRQ2_REG_SRC_FIRST_ILT_RT_OFFSET                          6681
#define PSWRQ2_REG_SRC_LAST_ILT_RT_OFFSET                           6682
#define PSWRQ2_REG_CDUC_FIRST_ILT_RT_OFFSET                         6683
#define PSWRQ2_REG_CDUC_LAST_ILT_RT_OFFSET                          6684
#define PSWRQ2_REG_CDUT_FIRST_ILT_RT_OFFSET                         6685
#define PSWRQ2_REG_CDUT_LAST_ILT_RT_OFFSET                          6686
#define PSWRQ2_REG_TSDM_FIRST_ILT_RT_OFFSET                         6687
#define PSWRQ2_REG_TSDM_LAST_ILT_RT_OFFSET                          6688
#define PSWRQ2_REG_TM_NUMBER_OF_PF_BLOCKS_RT_OFFSET                 6689
#define PSWRQ2_REG_CDUT_NUMBER_OF_PF_BLOCKS_RT_OFFSET               6690
#define PSWRQ2_REG_CDUC_NUMBER_OF_PF_BLOCKS_RT_OFFSET               6691
#define PSWRQ2_REG_TM_VF_BLOCKS_RT_OFFSET                           6692
#define PSWRQ2_REG_CDUT_VF_BLOCKS_RT_OFFSET                         6693
#define PSWRQ2_REG_CDUC_VF_BLOCKS_RT_OFFSET                         6694
#define PSWRQ2_REG_TM_BLOCKS_FACTOR_RT_OFFSET                       6695
#define PSWRQ2_REG_CDUT_BLOCKS_FACTOR_RT_OFFSET                     6696
#define PSWRQ2_REG_CDUC_BLOCKS_FACTOR_RT_OFFSET                     6697
#define PSWRQ2_REG_VF_BASE_RT_OFFSET                                6698
#define PSWRQ2_REG_VF_LAST_ILT_RT_OFFSET                            6699
#define PSWRQ2_REG_WR_MBS0_RT_OFFSET                                6700
#define PSWRQ2_REG_RD_MBS0_RT_OFFSET                                6701
#define PSWRQ2_REG_DRAM_ALIGN_WR_RT_OFFSET                          6702
#define PSWRQ2_REG_DRAM_ALIGN_RD_RT_OFFSET                          6703
#define PSWRQ2_REG_ILT_MEMORY_RT_OFFSET                             6704
#define PSWRQ2_REG_ILT_MEMORY_RT_SIZE                               22000
#define PGLUE_REG_B_VF_BASE_RT_OFFSET                               28704
#define PGLUE_REG_B_MSDM_OFFSET_MASK_B_RT_OFFSET                    28705
#define PGLUE_REG_B_MSDM_VF_SHIFT_B_RT_OFFSET                       28706
#define PGLUE_REG_B_CACHE_LINE_SIZE_RT_OFFSET                       28707
#define PGLUE_REG_B_PF_BAR0_SIZE_RT_OFFSET                          28708
#define PGLUE_REG_B_PF_BAR1_SIZE_RT_OFFSET                          28709
#define PGLUE_REG_B_VF_BAR1_SIZE_RT_OFFSET                          28710
#define TM_REG_VF_ENABLE_CONN_RT_OFFSET                             28711
#define TM_REG_PF_ENABLE_CONN_RT_OFFSET                             28712
#define TM_REG_PF_ENABLE_TASK_RT_OFFSET                             28713
#define TM_REG_GROUP_SIZE_RESOLUTION_CONN_RT_OFFSET                 28714
#define TM_REG_GROUP_SIZE_RESOLUTION_TASK_RT_OFFSET                 28715
#define TM_REG_CONFIG_CONN_MEM_RT_OFFSET                            28716
#define TM_REG_CONFIG_CONN_MEM_RT_SIZE                              416
#define TM_REG_CONFIG_TASK_MEM_RT_OFFSET                            29132
#define TM_REG_CONFIG_TASK_MEM_RT_SIZE                              608
#define QM_REG_MAXPQSIZE_0_RT_OFFSET                                29740
#define QM_REG_MAXPQSIZE_1_RT_OFFSET                                29741
#define QM_REG_MAXPQSIZE_2_RT_OFFSET                                29742
#define QM_REG_MAXPQSIZETXSEL_0_RT_OFFSET                           29743
#define QM_REG_MAXPQSIZETXSEL_1_RT_OFFSET                           29744
#define QM_REG_MAXPQSIZETXSEL_2_RT_OFFSET                           29745
#define QM_REG_MAXPQSIZETXSEL_3_RT_OFFSET                           29746
#define QM_REG_MAXPQSIZETXSEL_4_RT_OFFSET                           29747
#define QM_REG_MAXPQSIZETXSEL_5_RT_OFFSET                           29748
#define QM_REG_MAXPQSIZETXSEL_6_RT_OFFSET                           29749
#define QM_REG_MAXPQSIZETXSEL_7_RT_OFFSET                           29750
#define QM_REG_MAXPQSIZETXSEL_8_RT_OFFSET                           29751
#define QM_REG_MAXPQSIZETXSEL_9_RT_OFFSET                           29752
#define QM_REG_MAXPQSIZETXSEL_10_RT_OFFSET                          29753
#define QM_REG_MAXPQSIZETXSEL_11_RT_OFFSET                          29754
#define QM_REG_MAXPQSIZETXSEL_12_RT_OFFSET                          29755
#define QM_REG_MAXPQSIZETXSEL_13_RT_OFFSET                          29756
#define QM_REG_MAXPQSIZETXSEL_14_RT_OFFSET                          29757
#define QM_REG_MAXPQSIZETXSEL_15_RT_OFFSET                          29758
#define QM_REG_MAXPQSIZETXSEL_16_RT_OFFSET                          29759
#define QM_REG_MAXPQSIZETXSEL_17_RT_OFFSET                          29760
#define QM_REG_MAXPQSIZETXSEL_18_RT_OFFSET                          29761
#define QM_REG_MAXPQSIZETXSEL_19_RT_OFFSET                          29762
#define QM_REG_MAXPQSIZETXSEL_20_RT_OFFSET                          29763
#define QM_REG_MAXPQSIZETXSEL_21_RT_OFFSET                          29764
#define QM_REG_MAXPQSIZETXSEL_22_RT_OFFSET                          29765
#define QM_REG_MAXPQSIZETXSEL_23_RT_OFFSET                          29766
#define QM_REG_MAXPQSIZETXSEL_24_RT_OFFSET                          29767
#define QM_REG_MAXPQSIZETXSEL_25_RT_OFFSET                          29768
#define QM_REG_MAXPQSIZETXSEL_26_RT_OFFSET                          29769
#define QM_REG_MAXPQSIZETXSEL_27_RT_OFFSET                          29770
#define QM_REG_MAXPQSIZETXSEL_28_RT_OFFSET                          29771
#define QM_REG_MAXPQSIZETXSEL_29_RT_OFFSET                          29772
#define QM_REG_MAXPQSIZETXSEL_30_RT_OFFSET                          29773
#define QM_REG_MAXPQSIZETXSEL_31_RT_OFFSET                          29774
#define QM_REG_MAXPQSIZETXSEL_32_RT_OFFSET                          29775
#define QM_REG_MAXPQSIZETXSEL_33_RT_OFFSET                          29776
#define QM_REG_MAXPQSIZETXSEL_34_RT_OFFSET                          29777
#define QM_REG_MAXPQSIZETXSEL_35_RT_OFFSET                          29778
#define QM_REG_MAXPQSIZETXSEL_36_RT_OFFSET                          29779
#define QM_REG_MAXPQSIZETXSEL_37_RT_OFFSET                          29780
#define QM_REG_MAXPQSIZETXSEL_38_RT_OFFSET                          29781
#define QM_REG_MAXPQSIZETXSEL_39_RT_OFFSET                          29782
#define QM_REG_MAXPQSIZETXSEL_40_RT_OFFSET                          29783
#define QM_REG_MAXPQSIZETXSEL_41_RT_OFFSET                          29784
#define QM_REG_MAXPQSIZETXSEL_42_RT_OFFSET                          29785
#define QM_REG_MAXPQSIZETXSEL_43_RT_OFFSET                          29786
#define QM_REG_MAXPQSIZETXSEL_44_RT_OFFSET                          29787
#define QM_REG_MAXPQSIZETXSEL_45_RT_OFFSET                          29788
#define QM_REG_MAXPQSIZETXSEL_46_RT_OFFSET                          29789
#define QM_REG_MAXPQSIZETXSEL_47_RT_OFFSET                          29790
#define QM_REG_MAXPQSIZETXSEL_48_RT_OFFSET                          29791
#define QM_REG_MAXPQSIZETXSEL_49_RT_OFFSET                          29792
#define QM_REG_MAXPQSIZETXSEL_50_RT_OFFSET                          29793
#define QM_REG_MAXPQSIZETXSEL_51_RT_OFFSET                          29794
#define QM_REG_MAXPQSIZETXSEL_52_RT_OFFSET                          29795
#define QM_REG_MAXPQSIZETXSEL_53_RT_OFFSET                          29796
#define QM_REG_MAXPQSIZETXSEL_54_RT_OFFSET                          29797
#define QM_REG_MAXPQSIZETXSEL_55_RT_OFFSET                          29798
#define QM_REG_MAXPQSIZETXSEL_56_RT_OFFSET                          29799
#define QM_REG_MAXPQSIZETXSEL_57_RT_OFFSET                          29800
#define QM_REG_MAXPQSIZETXSEL_58_RT_OFFSET                          29801
#define QM_REG_MAXPQSIZETXSEL_59_RT_OFFSET                          29802
#define QM_REG_MAXPQSIZETXSEL_60_RT_OFFSET                          29803
#define QM_REG_MAXPQSIZETXSEL_61_RT_OFFSET                          29804
#define QM_REG_MAXPQSIZETXSEL_62_RT_OFFSET                          29805
#define QM_REG_MAXPQSIZETXSEL_63_RT_OFFSET                          29806
#define QM_REG_BASEADDROTHERPQ_RT_OFFSET                            29807
#define QM_REG_AFULLQMBYPTHRPFWFQ_RT_OFFSET                         29935
#define QM_REG_AFULLQMBYPTHRVPWFQ_RT_OFFSET                         29936
#define QM_REG_AFULLQMBYPTHRPFRL_RT_OFFSET                          29937
#define QM_REG_AFULLQMBYPTHRGLBLRL_RT_OFFSET                        29938
#define QM_REG_AFULLOPRTNSTCCRDMASK_RT_OFFSET                       29939
#define QM_REG_WRROTHERPQGRP_0_RT_OFFSET                            29940
#define QM_REG_WRROTHERPQGRP_1_RT_OFFSET                            29941
#define QM_REG_WRROTHERPQGRP_2_RT_OFFSET                            29942
#define QM_REG_WRROTHERPQGRP_3_RT_OFFSET                            29943
#define QM_REG_WRROTHERPQGRP_4_RT_OFFSET                            29944
#define QM_REG_WRROTHERPQGRP_5_RT_OFFSET                            29945
#define QM_REG_WRROTHERPQGRP_6_RT_OFFSET                            29946
#define QM_REG_WRROTHERPQGRP_7_RT_OFFSET                            29947
#define QM_REG_WRROTHERPQGRP_8_RT_OFFSET                            29948
#define QM_REG_WRROTHERPQGRP_9_RT_OFFSET                            29949
#define QM_REG_WRROTHERPQGRP_10_RT_OFFSET                           29950
#define QM_REG_WRROTHERPQGRP_11_RT_OFFSET                           29951
#define QM_REG_WRROTHERPQGRP_12_RT_OFFSET                           29952
#define QM_REG_WRROTHERPQGRP_13_RT_OFFSET                           29953
#define QM_REG_WRROTHERPQGRP_14_RT_OFFSET                           29954
#define QM_REG_WRROTHERPQGRP_15_RT_OFFSET                           29955
#define QM_REG_WRROTHERGRPWEIGHT_0_RT_OFFSET                        29956
#define QM_REG_WRROTHERGRPWEIGHT_1_RT_OFFSET                        29957
#define QM_REG_WRROTHERGRPWEIGHT_2_RT_OFFSET                        29958
#define QM_REG_WRROTHERGRPWEIGHT_3_RT_OFFSET                        29959
#define QM_REG_WRRTXGRPWEIGHT_0_RT_OFFSET                           29960
#define QM_REG_WRRTXGRPWEIGHT_1_RT_OFFSET                           29961
#define QM_REG_PQTX2PF_0_RT_OFFSET                                  29962
#define QM_REG_PQTX2PF_1_RT_OFFSET                                  29963
#define QM_REG_PQTX2PF_2_RT_OFFSET                                  29964
#define QM_REG_PQTX2PF_3_RT_OFFSET                                  29965
#define QM_REG_PQTX2PF_4_RT_OFFSET                                  29966
#define QM_REG_PQTX2PF_5_RT_OFFSET                                  29967
#define QM_REG_PQTX2PF_6_RT_OFFSET                                  29968
#define QM_REG_PQTX2PF_7_RT_OFFSET                                  29969
#define QM_REG_PQTX2PF_8_RT_OFFSET                                  29970
#define QM_REG_PQTX2PF_9_RT_OFFSET                                  29971
#define QM_REG_PQTX2PF_10_RT_OFFSET                                 29972
#define QM_REG_PQTX2PF_11_RT_OFFSET                                 29973
#define QM_REG_PQTX2PF_12_RT_OFFSET                                 29974
#define QM_REG_PQTX2PF_13_RT_OFFSET                                 29975
#define QM_REG_PQTX2PF_14_RT_OFFSET                                 29976
#define QM_REG_PQTX2PF_15_RT_OFFSET                                 29977
#define QM_REG_PQTX2PF_16_RT_OFFSET                                 29978
#define QM_REG_PQTX2PF_17_RT_OFFSET                                 29979
#define QM_REG_PQTX2PF_18_RT_OFFSET                                 29980
#define QM_REG_PQTX2PF_19_RT_OFFSET                                 29981
#define QM_REG_PQTX2PF_20_RT_OFFSET                                 29982
#define QM_REG_PQTX2PF_21_RT_OFFSET                                 29983
#define QM_REG_PQTX2PF_22_RT_OFFSET                                 29984
#define QM_REG_PQTX2PF_23_RT_OFFSET                                 29985
#define QM_REG_PQTX2PF_24_RT_OFFSET                                 29986
#define QM_REG_PQTX2PF_25_RT_OFFSET                                 29987
#define QM_REG_PQTX2PF_26_RT_OFFSET                                 29988
#define QM_REG_PQTX2PF_27_RT_OFFSET                                 29989
#define QM_REG_PQTX2PF_28_RT_OFFSET                                 29990
#define QM_REG_PQTX2PF_29_RT_OFFSET                                 29991
#define QM_REG_PQTX2PF_30_RT_OFFSET                                 29992
#define QM_REG_PQTX2PF_31_RT_OFFSET                                 29993
#define QM_REG_PQTX2PF_32_RT_OFFSET                                 29994
#define QM_REG_PQTX2PF_33_RT_OFFSET                                 29995
#define QM_REG_PQTX2PF_34_RT_OFFSET                                 29996
#define QM_REG_PQTX2PF_35_RT_OFFSET                                 29997
#define QM_REG_PQTX2PF_36_RT_OFFSET                                 29998
#define QM_REG_PQTX2PF_37_RT_OFFSET                                 29999
#define QM_REG_PQTX2PF_38_RT_OFFSET                                 30000
#define QM_REG_PQTX2PF_39_RT_OFFSET                                 30001
#define QM_REG_PQTX2PF_40_RT_OFFSET                                 30002
#define QM_REG_PQTX2PF_41_RT_OFFSET                                 30003
#define QM_REG_PQTX2PF_42_RT_OFFSET                                 30004
#define QM_REG_PQTX2PF_43_RT_OFFSET                                 30005
#define QM_REG_PQTX2PF_44_RT_OFFSET                                 30006
#define QM_REG_PQTX2PF_45_RT_OFFSET                                 30007
#define QM_REG_PQTX2PF_46_RT_OFFSET                                 30008
#define QM_REG_PQTX2PF_47_RT_OFFSET                                 30009
#define QM_REG_PQTX2PF_48_RT_OFFSET                                 30010
#define QM_REG_PQTX2PF_49_RT_OFFSET                                 30011
#define QM_REG_PQTX2PF_50_RT_OFFSET                                 30012
#define QM_REG_PQTX2PF_51_RT_OFFSET                                 30013
#define QM_REG_PQTX2PF_52_RT_OFFSET                                 30014
#define QM_REG_PQTX2PF_53_RT_OFFSET                                 30015
#define QM_REG_PQTX2PF_54_RT_OFFSET                                 30016
#define QM_REG_PQTX2PF_55_RT_OFFSET                                 30017
#define QM_REG_PQTX2PF_56_RT_OFFSET                                 30018
#define QM_REG_PQTX2PF_57_RT_OFFSET                                 30019
#define QM_REG_PQTX2PF_58_RT_OFFSET                                 30020
#define QM_REG_PQTX2PF_59_RT_OFFSET                                 30021
#define QM_REG_PQTX2PF_60_RT_OFFSET                                 30022
#define QM_REG_PQTX2PF_61_RT_OFFSET                                 30023
#define QM_REG_PQTX2PF_62_RT_OFFSET                                 30024
#define QM_REG_PQTX2PF_63_RT_OFFSET                                 30025
#define QM_REG_PQOTHER2PF_0_RT_OFFSET                               30026
#define QM_REG_PQOTHER2PF_1_RT_OFFSET                               30027
#define QM_REG_PQOTHER2PF_2_RT_OFFSET                               30028
#define QM_REG_PQOTHER2PF_3_RT_OFFSET                               30029
#define QM_REG_PQOTHER2PF_4_RT_OFFSET                               30030
#define QM_REG_PQOTHER2PF_5_RT_OFFSET                               30031
#define QM_REG_PQOTHER2PF_6_RT_OFFSET                               30032
#define QM_REG_PQOTHER2PF_7_RT_OFFSET                               30033
#define QM_REG_PQOTHER2PF_8_RT_OFFSET                               30034
#define QM_REG_PQOTHER2PF_9_RT_OFFSET                               30035
#define QM_REG_PQOTHER2PF_10_RT_OFFSET                              30036
#define QM_REG_PQOTHER2PF_11_RT_OFFSET                              30037
#define QM_REG_PQOTHER2PF_12_RT_OFFSET                              30038
#define QM_REG_PQOTHER2PF_13_RT_OFFSET                              30039
#define QM_REG_PQOTHER2PF_14_RT_OFFSET                              30040
#define QM_REG_PQOTHER2PF_15_RT_OFFSET                              30041
#define QM_REG_RLGLBLPERIOD_0_RT_OFFSET                             30042
#define QM_REG_RLGLBLPERIOD_1_RT_OFFSET                             30043
#define QM_REG_RLGLBLPERIODTIMER_0_RT_OFFSET                        30044
#define QM_REG_RLGLBLPERIODTIMER_1_RT_OFFSET                        30045
#define QM_REG_RLGLBLPERIODSEL_0_RT_OFFSET                          30046
#define QM_REG_RLGLBLPERIODSEL_1_RT_OFFSET                          30047
#define QM_REG_RLGLBLPERIODSEL_2_RT_OFFSET                          30048
#define QM_REG_RLGLBLPERIODSEL_3_RT_OFFSET                          30049
#define QM_REG_RLGLBLPERIODSEL_4_RT_OFFSET                          30050
#define QM_REG_RLGLBLPERIODSEL_5_RT_OFFSET                          30051
#define QM_REG_RLGLBLPERIODSEL_6_RT_OFFSET                          30052
#define QM_REG_RLGLBLPERIODSEL_7_RT_OFFSET                          30053
#define QM_REG_RLGLBLINCVAL_RT_OFFSET                               30054
#define QM_REG_RLGLBLINCVAL_RT_SIZE                                 256
#define QM_REG_RLGLBLUPPERBOUND_RT_OFFSET                           30310
#define QM_REG_RLGLBLUPPERBOUND_RT_SIZE                             256
#define QM_REG_RLGLBLCRD_RT_OFFSET                                  30566
#define QM_REG_RLGLBLCRD_RT_SIZE                                    256
#define QM_REG_RLGLBLENABLE_RT_OFFSET                               30822
#define QM_REG_RLPFPERIOD_RT_OFFSET                                 30823
#define QM_REG_RLPFPERIODTIMER_RT_OFFSET                            30824
#define QM_REG_RLPFINCVAL_RT_OFFSET                                 30825
#define QM_REG_RLPFINCVAL_RT_SIZE                                   16
#define QM_REG_RLPFUPPERBOUND_RT_OFFSET                             30841
#define QM_REG_RLPFUPPERBOUND_RT_SIZE                               16
#define QM_REG_RLPFCRD_RT_OFFSET                                    30857
#define QM_REG_RLPFCRD_RT_SIZE                                      16
#define QM_REG_RLPFENABLE_RT_OFFSET                                 30873
#define QM_REG_RLPFVOQENABLE_RT_OFFSET                              30874
#define QM_REG_WFQPFWEIGHT_RT_OFFSET                                30875
#define QM_REG_WFQPFWEIGHT_RT_SIZE                                  16
#define QM_REG_WFQPFUPPERBOUND_RT_OFFSET                            30891
#define QM_REG_WFQPFUPPERBOUND_RT_SIZE                              16
#define QM_REG_WFQPFCRD_RT_OFFSET                                   30907
#define QM_REG_WFQPFCRD_RT_SIZE                                     256
#define QM_REG_WFQPFENABLE_RT_OFFSET                                31163
#define QM_REG_WFQVPENABLE_RT_OFFSET                                31164
#define QM_REG_BASEADDRTXPQ_RT_OFFSET                               31165
#define QM_REG_BASEADDRTXPQ_RT_SIZE                                 512
#define QM_REG_TXPQMAP_RT_OFFSET                                    31677
#define QM_REG_TXPQMAP_RT_SIZE                                      512
#define QM_REG_WFQVPWEIGHT_RT_OFFSET                                32189
#define QM_REG_WFQVPWEIGHT_RT_SIZE                                  512
#define QM_REG_WFQVPCRD_RT_OFFSET                                   32701
#define QM_REG_WFQVPCRD_RT_SIZE                                     512
#define QM_REG_WFQVPMAP_RT_OFFSET                                   33213
#define QM_REG_WFQVPMAP_RT_SIZE                                     512
#define QM_REG_WFQPFCRD_MSB_RT_OFFSET                               33725
#define QM_REG_WFQPFCRD_MSB_RT_SIZE                                 320
#define QM_REG_VOQCRDLINE_RT_OFFSET                                 34045
#define QM_REG_VOQCRDLINE_RT_SIZE                                   36
#define QM_REG_VOQINITCRDLINE_RT_OFFSET                             34081
#define QM_REG_VOQINITCRDLINE_RT_SIZE                               36
#define NIG_REG_TAG_ETHERTYPE_0_RT_OFFSET                           34117
#define NIG_REG_OUTER_TAG_VALUE_LIST0_RT_OFFSET                     34118
#define NIG_REG_OUTER_TAG_VALUE_LIST1_RT_OFFSET                     34119
#define NIG_REG_OUTER_TAG_VALUE_LIST2_RT_OFFSET                     34120
#define NIG_REG_OUTER_TAG_VALUE_LIST3_RT_OFFSET                     34121
#define NIG_REG_OUTER_TAG_VALUE_MASK_RT_OFFSET                      34122
#define NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET                  34123
#define NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET                           34124
#define NIG_REG_LLH_FUNC_TAG_EN_RT_SIZE                             4
#define NIG_REG_LLH_FUNC_TAG_HDR_SEL_RT_OFFSET                      34128
#define NIG_REG_LLH_FUNC_TAG_HDR_SEL_RT_SIZE                        4
#define NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET                        34132
#define NIG_REG_LLH_FUNC_TAG_VALUE_RT_SIZE                          4
#define NIG_REG_LLH_FUNC_NO_TAG_RT_OFFSET                           34136
#define NIG_REG_LLH_FUNC_FILTER_VALUE_RT_OFFSET                     34137
#define NIG_REG_LLH_FUNC_FILTER_VALUE_RT_SIZE                       32
#define NIG_REG_LLH_FUNC_FILTER_EN_RT_OFFSET                        34169
#define NIG_REG_LLH_FUNC_FILTER_EN_RT_SIZE                          16
#define NIG_REG_LLH_FUNC_FILTER_MODE_RT_OFFSET                      34185
#define NIG_REG_LLH_FUNC_FILTER_MODE_RT_SIZE                        16
#define NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE_RT_OFFSET             34201
#define NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE_RT_SIZE               16
#define NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_OFFSET                   34217
#define NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_SIZE                     16
#define NIG_REG_TX_EDPM_CTRL_RT_OFFSET                              34233
#define NIG_REG_ROCE_DUPLICATE_TO_HOST_RT_OFFSET                    34234
#define CDU_REG_CID_ADDR_PARAMS_RT_OFFSET                           34235
#define CDU_REG_SEGMENT0_PARAMS_RT_OFFSET                           34236
#define CDU_REG_SEGMENT1_PARAMS_RT_OFFSET                           34237
#define CDU_REG_PF_SEG0_TYPE_OFFSET_RT_OFFSET                       34238
#define CDU_REG_PF_SEG1_TYPE_OFFSET_RT_OFFSET                       34239
#define CDU_REG_PF_SEG2_TYPE_OFFSET_RT_OFFSET                       34240
#define CDU_REG_PF_SEG3_TYPE_OFFSET_RT_OFFSET                       34241
#define CDU_REG_PF_FL_SEG0_TYPE_OFFSET_RT_OFFSET                    34242
#define CDU_REG_PF_FL_SEG1_TYPE_OFFSET_RT_OFFSET                    34243
#define CDU_REG_PF_FL_SEG2_TYPE_OFFSET_RT_OFFSET                    34244
#define CDU_REG_PF_FL_SEG3_TYPE_OFFSET_RT_OFFSET                    34245
#define CDU_REG_VF_SEG_TYPE_OFFSET_RT_OFFSET                        34246
#define CDU_REG_VF_FL_SEG_TYPE_OFFSET_RT_OFFSET                     34247
#define PBF_REG_TAG_ETHERTYPE_0_RT_OFFSET                           34248
#define PBF_REG_BTB_SHARED_AREA_SIZE_RT_OFFSET                      34249
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ0_RT_OFFSET                    34250
#define PBF_REG_BTB_GUARANTEED_VOQ0_RT_OFFSET                       34251
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ0_RT_OFFSET                34252
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ1_RT_OFFSET                    34253
#define PBF_REG_BTB_GUARANTEED_VOQ1_RT_OFFSET                       34254
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ1_RT_OFFSET                34255
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ2_RT_OFFSET                    34256
#define PBF_REG_BTB_GUARANTEED_VOQ2_RT_OFFSET                       34257
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ2_RT_OFFSET                34258
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ3_RT_OFFSET                    34259
#define PBF_REG_BTB_GUARANTEED_VOQ3_RT_OFFSET                       34260
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ3_RT_OFFSET                34261
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ4_RT_OFFSET                    34262
#define PBF_REG_BTB_GUARANTEED_VOQ4_RT_OFFSET                       34263
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ4_RT_OFFSET                34264
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ5_RT_OFFSET                    34265
#define PBF_REG_BTB_GUARANTEED_VOQ5_RT_OFFSET                       34266
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ5_RT_OFFSET                34267
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ6_RT_OFFSET                    34268
#define PBF_REG_BTB_GUARANTEED_VOQ6_RT_OFFSET                       34269
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ6_RT_OFFSET                34270
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ7_RT_OFFSET                    34271
#define PBF_REG_BTB_GUARANTEED_VOQ7_RT_OFFSET                       34272
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ7_RT_OFFSET                34273
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ8_RT_OFFSET                    34274
#define PBF_REG_BTB_GUARANTEED_VOQ8_RT_OFFSET                       34275
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ8_RT_OFFSET                34276
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ9_RT_OFFSET                    34277
#define PBF_REG_BTB_GUARANTEED_VOQ9_RT_OFFSET                       34278
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ9_RT_OFFSET                34279
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ10_RT_OFFSET                   34280
#define PBF_REG_BTB_GUARANTEED_VOQ10_RT_OFFSET                      34281
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ10_RT_OFFSET               34282
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ11_RT_OFFSET                   34283
#define PBF_REG_BTB_GUARANTEED_VOQ11_RT_OFFSET                      34284
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ11_RT_OFFSET               34285
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ12_RT_OFFSET                   34286
#define PBF_REG_BTB_GUARANTEED_VOQ12_RT_OFFSET                      34287
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ12_RT_OFFSET               34288
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ13_RT_OFFSET                   34289
#define PBF_REG_BTB_GUARANTEED_VOQ13_RT_OFFSET                      34290
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ13_RT_OFFSET               34291
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ14_RT_OFFSET                   34292
#define PBF_REG_BTB_GUARANTEED_VOQ14_RT_OFFSET                      34293
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ14_RT_OFFSET               34294
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ15_RT_OFFSET                   34295
#define PBF_REG_BTB_GUARANTEED_VOQ15_RT_OFFSET                      34296
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ15_RT_OFFSET               34297
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ16_RT_OFFSET                   34298
#define PBF_REG_BTB_GUARANTEED_VOQ16_RT_OFFSET                      34299
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ16_RT_OFFSET               34300
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ17_RT_OFFSET                   34301
#define PBF_REG_BTB_GUARANTEED_VOQ17_RT_OFFSET                      34302
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ17_RT_OFFSET               34303
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ18_RT_OFFSET                   34304
#define PBF_REG_BTB_GUARANTEED_VOQ18_RT_OFFSET                      34305
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ18_RT_OFFSET               34306
#define PBF_REG_YCMD_QS_NUM_LINES_VOQ19_RT_OFFSET                   34307
#define PBF_REG_BTB_GUARANTEED_VOQ19_RT_OFFSET                      34308
#define PBF_REG_BTB_SHARED_AREA_SETUP_VOQ19_RT_OFFSET               34309
#define XCM_REG_CON_PHY_Q3_RT_OFFSET                                34310

#define RUNTIME_ARRAY_SIZE 34311

#endif /* __RT_DEFS_H__ */
