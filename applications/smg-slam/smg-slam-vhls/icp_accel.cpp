//#define __OPENCV__
#include "icp.h"
#include "icp_accel.h"
//#include "math.h"
#include "hls_stream.h"
#include <string.h>
#include <ap_int.h>
#include "hls_math.h"
//#include "stdlib.h"


#ifdef __OPENCV__
extern std::string mapTitle;
extern IplImage *mapDisplay;
#endif

#define RANND_MAX_SIZE 1024

const unsigned int rand_matrix[RANND_MAX_SIZE] = { 41, 18467, 6334, 26500, 19169, 15724, 11478, 29358, 26962, 24464, 5705, 28145, 23281, 16827, 9961, 491, 2995, 11942, 4827, 5436, 32391, 14604, 3902, 153, 292, 12382, 17421, 18716, 19718, 19895, 5447, 21726,
14771, 11538, 1869, 19912, 25667, 26299, 17035, 9894, 28703, 23811, 31322, 30333, 17673, 4664, 15141, 7711, 28253, 6868, 25547, 27644, 32662, 32757, 20037, 12859, 8723, 9741, 27529, 778, 12316, 3035, 22190, 1842,
288, 30106, 9040, 8942, 19264, 22648, 27446, 23805, 15890, 6729, 24370, 15350, 15006, 31101, 24393, 3548, 19629, 12623, 24084, 19954, 18756, 11840, 4966, 7376, 13931, 26308, 16944, 32439, 24626, 11323, 5537, 21538,
16118, 2082, 22929, 16541, 4833, 31115, 4639, 29658, 22704, 9930, 13977, 2306, 31673, 22386, 5021, 28745, 26924, 19072, 6270, 5829, 26777, 15573, 5097, 16512, 23986, 13290, 9161, 18636, 22355, 24767, 23655, 15574,
4031, 12052, 27350, 1150, 16941, 21724, 13966, 3430, 31107, 30191, 18007, 11337, 15457, 12287, 27753, 10383, 14945, 8909, 32209, 9758, 24221, 18588, 6422, 24946, 27506, 13030, 16413, 29168, 900, 32591, 18762, 1655,
17410, 6359, 27624, 20537, 21548, 6483, 27595, 4041, 3602, 24350, 10291, 30836, 9374, 11020, 4596, 24021, 27348, 23199, 19668, 24484, 8281, 4734, 53, 1999, 26418, 27938, 6900, 3788, 18127, 467, 3728, 14893,
24648, 22483, 17807, 2421, 14310, 6617, 22813, 9514, 14309, 7616, 18935, 17451, 20600, 5249, 16519, 31556, 22798, 30303, 6224, 11008, 5844, 32609, 14989, 32702, 3195, 20485, 3093, 14343, 30523, 1587, 29314, 9503,
7448, 25200, 13458, 6618, 20580, 19796, 14798, 15281, 19589, 20798, 28009, 27157, 20472, 23622, 18538, 12292, 6038, 24179, 18190, 29657, 7958, 6191, 19815, 22888, 19156, 11511, 16202, 2634, 24272, 20055, 20328, 22646,
26362, 4886, 18875, 28433, 29869, 20142, 23844, 1416, 21881, 31998, 10322, 18651, 10021, 5699, 3557, 28476, 27892, 24389, 5075, 10712, 2600, 2510, 21003, 26869, 17861, 14688, 13401, 9789, 15255, 16423, 5002, 10585,
24182, 10285, 27088, 31426, 28617, 23757, 9832, 30932, 4169, 2154, 25721, 17189, 19976, 31329, 2368, 28692, 21425, 10555, 3434, 16549, 7441, 9512, 30145, 18060, 21718, 3753, 16139, 12423, 16279, 25996, 16687, 12529,
22549, 17437, 19866, 12949, 193, 23195, 3297, 20416, 28286, 16105, 24488, 16282, 12455, 25734, 18114, 11701, 31316, 20671, 5786, 12263, 4313, 24355, 31185, 20053, 912, 10808, 1832, 20945, 4313, 27756,28321, 19558,
23646, 27982, 481, 4144, 23196, 20222, 7129, 2161, 5535, 20450, 11173, 10466, 12044, 21659, 26292, 26439, 17253, 20024, 26154, 29510, 4745, 20649, 13186, 8313, 4474, 28022, 2168, 14018, 18787, 9905, 17958, 7391,
10202, 3625, 26477, 4414, 9314, 25824, 29334, 25874, 24372, 20159, 11833, 28070, 7487, 28297, 7518, 8177, 17773, 32270, 1763, 2668, 17192, 13985, 3102, 8480, 29213, 7627, 4802, 4099, 30527, 2625, 1543, 1924,
11023, 29972, 13061, 14181, 31003, 27432, 17505, 27593, 22725, 13031, 8492, 142, 17222, 31286, 13064, 7900, 19187, 8360, 22413, 30974, 14270, 29170, 235, 30833, 19711, 25760, 18896, 4667, 7285, 12550,140, 13694,
2695, 21624, 28019, 2125, 26576, 21694, 22658, 26302, 17371, 22466, 4678, 22593, 23851, 25484, 1018, 28464, 21119, 23152, 2800, 18087, 31060, 1926, 9010, 4757, 32170, 20315, 9576, 30227, 12043, 22758,7164, 5109,
7882, 17086, 29565, 3487, 29577, 14474, 2625, 25627, 5629, 31928, 25423, 28520, 6902, 14962, 123, 24596, 3737, 13261, 10195, 32525, 1264, 8260, 6202, 8116, 5030, 20326, 29011, 30771, 6411, 25547, 21153, 21520,
29790, 14924, 30188, 21763, 4940, 20851, 18662, 13829, 30900, 17713, 18958, 17578, 8365, 13007, 11477, 1200, 26058, 6439, 2303, 12760, 19357, 2324, 6477, 5108, 21113, 14887, 19801, 22850, 14460, 22428, 12993, 27384,
19405, 6540, 31111, 28704, 12835, 32356, 6072, 29350, 18823, 14485, 20556, 23216, 1626, 9357, 8526, 13357, 29337, 23271, 23869, 29361, 12896, 13022, 29617, 10112, 12717, 18696, 11585, 24041, 24423, 24129, 24229, 4565,
6559, 8932, 22296, 29855, 12053, 16962, 3584, 29734, 6654, 16972, 21457, 14369, 22532, 2963, 2607, 2483, 911, 11635, 10067, 22848, 4675, 12938, 2223, 22142, 23754, 6511, 22741, 20175, 21459, 17825, 3221, 17870,
1626, 31934, 15205, 31783, 23850, 17398, 22279, 22701, 12193, 12734, 1637, 26534, 5556, 1993, 10176, 25705, 6962, 10548, 15881, 300, 14413, 16641, 19855, 24855, 13142, 11462, 27611, 30877, 20424, 32678, 1752, 18443,
28296, 12673, 10040, 9313, 875, 20072, 12818, 610, 1017, 14932, 28112, 30695, 13169, 23831, 20040, 26488, 28685, 19090, 19497, 2589, 25990, 15145, 19353, 19314, 18651, 26740, 22044, 11258, 335, 8759,11192, 7605,
25264, 12181, 28503, 3829, 23775, 20608, 29292, 5997, 17549, 29556, 25561, 31627, 6467, 29541, 26129, 31240, 27813, 29174, 20601, 6077, 20215, 8683, 8213, 23992, 25824, 5601, 23392, 15759, 2670, 26428, 28027, 4084,
10075, 18786, 15498, 24970, 6287, 23847, 32604, 503, 21221, 22663, 5706, 2363, 9010, 22171, 27489, 18240, 12164, 25542, 7619, 20913, 7591, 6704, 31818, 9232, 750, 25205, 4975, 1539, 303, 11422, 21098,11247,
13584, 13648, 2971, 17864, 22913, 11075, 21545, 28712, 17546, 18678, 1769, 15262, 8519, 13985, 28289, 15944, 2865, 18540, 23245, 25508, 28318, 27870, 9601, 28323, 21132, 24472, 27152, 25087, 28570, 29763, 29901, 17103,
14423, 3527, 11600, 26969, 14015, 5565, 28, 21543, 25347, 2088, 2943, 12637, 22409, 26463, 5049, 4681, 1588, 11342, 608, 32060, 21221, 1758, 29954, 20888, 14146, 690, 7949, 12843, 21430, 25620, 748, 27067,
4536, 20783, 18035, 32226, 15185, 7038, 9853, 25629, 11224, 15748, 19923, 3359, 32257, 24766, 4944, 14955, 23318, 32726, 25411, 21025, 20355, 31001, 22549, 9496, 18584, 9515, 17964, 23342, 8075, 17913, 16142, 31196,
21948, 25072, 20426, 14606, 26173, 24429, 32404, 6705, 20626, 29812, 19375, 30093, 16565, 16036, 14736, 29141, 30814, 5994, 8256, 6652, 23936, 30838, 20482, 1355, 21015, 1131, 18230, 17841, 14625, 2011, 32637, 4186,
19690, 1650, 5662, 21634, 10893, 10353, 21416, 13452, 14008, 7262, 22233, 5454, 16303, 16634, 26303, 14256, 148, 11124, 12317, 4213, 27109, 24028, 29200, 21080, 21318, 16858, 24050, 24155, 31361, 15264, 11903, 3676,
29643, 26909, 14902, 3561, 28489, 24948, 1282, 13653, 30674, 2220, 5402, 6923, 3831, 19369, 3878, 20259, 19008, 22619, 23971, 30003, 21945, 9781, 26504, 12392, 32685, 25313, 6698, 5589, 12722, 5938, 19037, 6410,
31461, 6234, 12508, 9961, 3959, 6493, 1515, 25269, 24937, 28869, 58, 14700, 13971, 26264, 15117, 16215, 24555, 7815, 18330, 3039, 30212, 29288, 28082, 1954, 16085, 20710, 24484, 24774, 8380, 29815, 25951, 6541,
18115, 1679, 17110, 25898, 23073, 788, 23977, 18132, 29956, 28689, 26113, 10008, 12941, 15790, 1723, 21363, 28, 25184, 24778, 7200, 5071, 1885, 21974, 1071, 11333, 22867, 26153, 14295, 32168, 20825, 9676, 15629,
28650, 2598, 3309, 4693, 4686, 30080, 10116, 12249, 26667, 1528, 26679, 7864, 29421, 8405, 8826, 6816, 7516, 27726, 28666, 29087, 27681, 19964, 1340, 5686, 6021, 11662, 14721, 6064, 29309, 20415, 17902, 29873
};

const unsigned int rand_matrix_3[RANND_MAX_SIZE] = { 41, 18467, 6334, 26500, 19169, 15724, 11478, 29358, 26962, 24464, 5705, 28145, 23281, 16827, 9961, 491, 2995, 11942, 4827, 5436, 32391, 14604, 3902, 153, 292, 12382, 17421, 18716, 19718, 19895, 5447, 21726,
14771, 11538, 1869, 19912, 25667, 26299, 17035, 9894, 28703, 23811, 31322, 30333, 17673, 4664, 15141, 7711, 28253, 6868, 25547, 27644, 32662, 32757, 20037, 12859, 8723, 9741, 27529, 778, 12316, 3035, 22190, 1842,
288, 30106, 9040, 8942, 19264, 22648, 27446, 23805, 15890, 6729, 24370, 15350, 15006, 31101, 24393, 3548, 19629, 12623, 24084, 19954, 18756, 11840, 4966, 7376, 13931, 26308, 16944, 32439, 24626, 11323, 5537, 21538,
16118, 2082, 22929, 16541, 4833, 31115, 4639, 29658, 22704, 9930, 13977, 2306, 31673, 22386, 5021, 28745, 26924, 19072, 6270, 5829, 26777, 15573, 5097, 16512, 23986, 13290, 9161, 18636, 22355, 24767, 23655, 15574,
4031, 12052, 27350, 1150, 16941, 21724, 13966, 3430, 31107, 30191, 18007, 11337, 15457, 12287, 27753, 10383, 14945, 8909, 32209, 9758, 24221, 18588, 6422, 24946, 27506, 13030, 16413, 29168, 900, 32591, 18762, 1655,
17410, 6359, 27624, 20537, 21548, 6483, 27595, 4041, 3602, 24350, 10291, 30836, 9374, 11020, 4596, 24021, 27348, 23199, 19668, 24484, 8281, 4734, 53, 1999, 26418, 27938, 6900, 3788, 18127, 467, 3728, 14893,
24648, 22483, 17807, 2421, 14310, 6617, 22813, 9514, 14309, 7616, 18935, 17451, 20600, 5249, 16519, 31556, 22798, 30303, 6224, 11008, 5844, 32609, 14989, 32702, 3195, 20485, 3093, 14343, 30523, 1587, 29314, 9503,
7448, 25200, 13458, 6618, 20580, 19796, 14798, 15281, 19589, 20798, 28009, 27157, 20472, 23622, 18538, 12292, 6038, 24179, 18190, 29657, 7958, 6191, 19815, 22888, 19156, 11511, 16202, 2634, 24272, 20055, 20328, 22646,
26362, 4886, 18875, 28433, 29869, 20142, 23844, 1416, 21881, 31998, 10322, 18651, 10021, 5699, 3557, 28476, 27892, 24389, 5075, 10712, 2600, 2510, 21003, 26869, 17861, 14688, 13401, 9789, 15255, 16423, 5002, 10585,
24182, 10285, 27088, 31426, 28617, 23757, 9832, 30932, 4169, 2154, 25721, 17189, 19976, 31329, 2368, 28692, 21425, 10555, 3434, 16549, 7441, 9512, 30145, 18060, 21718, 3753, 16139, 12423, 16279, 25996, 16687, 12529,
22549, 17437, 19866, 12949, 193, 23195, 3297, 20416, 28286, 16105, 24488, 16282, 12455, 25734, 18114, 11701, 31316, 20671, 5786, 12263, 4313, 24355, 31185, 20053, 912, 10808, 1832, 20945, 4313, 27756,28321, 19558,
23646, 27982, 481, 4144, 23196, 20222, 7129, 2161, 5535, 20450, 11173, 10466, 12044, 21659, 26292, 26439, 17253, 20024, 26154, 29510, 4745, 20649, 13186, 8313, 4474, 28022, 2168, 14018, 18787, 9905, 17958, 7391,
10202, 3625, 26477, 4414, 9314, 25824, 29334, 25874, 24372, 20159, 11833, 28070, 7487, 28297, 7518, 8177, 17773, 32270, 1763, 2668, 17192, 13985, 3102, 8480, 29213, 7627, 4802, 4099, 30527, 2625, 1543, 1924,
11023, 29972, 13061, 14181, 31003, 27432, 17505, 27593, 22725, 13031, 8492, 142, 17222, 31286, 13064, 7900, 19187, 8360, 22413, 30974, 14270, 29170, 235, 30833, 19711, 25760, 18896, 4667, 7285, 12550,140, 13694,
2695, 21624, 28019, 2125, 26576, 21694, 22658, 26302, 17371, 22466, 4678, 22593, 23851, 25484, 1018, 28464, 21119, 23152, 2800, 18087, 31060, 1926, 9010, 4757, 32170, 20315, 9576, 30227, 12043, 22758,7164, 5109,
7882, 17086, 29565, 3487, 29577, 14474, 2625, 25627, 5629, 31928, 25423, 28520, 6902, 14962, 123, 24596, 3737, 13261, 10195, 32525, 1264, 8260, 6202, 8116, 5030, 20326, 29011, 30771, 6411, 25547, 21153, 21520,
29790, 14924, 30188, 21763, 4940, 20851, 18662, 13829, 30900, 17713, 18958, 17578, 8365, 13007, 11477, 1200, 26058, 6439, 2303, 12760, 19357, 2324, 6477, 5108, 21113, 14887, 19801, 22850, 14460, 22428, 12993, 27384,
19405, 6540, 31111, 28704, 12835, 32356, 6072, 29350, 18823, 14485, 20556, 23216, 1626, 9357, 8526, 13357, 29337, 23271, 23869, 29361, 12896, 13022, 29617, 10112, 12717, 18696, 11585, 24041, 24423, 24129, 24229, 4565,
6559, 8932, 22296, 29855, 12053, 16962, 3584, 29734, 6654, 16972, 21457, 14369, 22532, 2963, 2607, 2483, 911, 11635, 10067, 22848, 4675, 12938, 2223, 22142, 23754, 6511, 22741, 20175, 21459, 17825, 3221, 17870,
1626, 31934, 15205, 31783, 23850, 17398, 22279, 22701, 12193, 12734, 1637, 26534, 5556, 1993, 10176, 25705, 6962, 10548, 15881, 300, 14413, 16641, 19855, 24855, 13142, 11462, 27611, 30877, 20424, 32678, 1752, 18443,
28296, 12673, 10040, 9313, 875, 20072, 12818, 610, 1017, 14932, 28112, 30695, 13169, 23831, 20040, 26488, 28685, 19090, 19497, 2589, 25990, 15145, 19353, 19314, 18651, 26740, 22044, 11258, 335, 8759,11192, 7605,
25264, 12181, 28503, 3829, 23775, 20608, 29292, 5997, 17549, 29556, 25561, 31627, 6467, 29541, 26129, 31240, 27813, 29174, 20601, 6077, 20215, 8683, 8213, 23992, 25824, 5601, 23392, 15759, 2670, 26428, 28027, 4084,
10075, 18786, 15498, 24970, 6287, 23847, 32604, 503, 21221, 22663, 5706, 2363, 9010, 22171, 27489, 18240, 12164, 25542, 7619, 20913, 7591, 6704, 31818, 9232, 750, 25205, 4975, 1539, 303, 11422, 21098,11247,
13584, 13648, 2971, 17864, 22913, 11075, 21545, 28712, 17546, 18678, 1769, 15262, 8519, 13985, 28289, 15944, 2865, 18540, 23245, 25508, 28318, 27870, 9601, 28323, 21132, 24472, 27152, 25087, 28570, 29763, 29901, 17103,
14423, 3527, 11600, 26969, 14015, 5565, 28, 21543, 25347, 2088, 2943, 12637, 22409, 26463, 5049, 4681, 1588, 11342, 608, 32060, 21221, 1758, 29954, 20888, 14146, 690, 7949, 12843, 21430, 25620, 748, 27067,
4536, 20783, 18035, 32226, 15185, 7038, 9853, 25629, 11224, 15748, 19923, 3359, 32257, 24766, 4944, 14955, 23318, 32726, 25411, 21025, 20355, 31001, 22549, 9496, 18584, 9515, 17964, 23342, 8075, 17913, 16142, 31196,
21948, 25072, 20426, 14606, 26173, 24429, 32404, 6705, 20626, 29812, 19375, 30093, 16565, 16036, 14736, 29141, 30814, 5994, 8256, 6652, 23936, 30838, 20482, 1355, 21015, 1131, 18230, 17841, 14625, 2011, 32637, 4186,
19690, 1650, 5662, 21634, 10893, 10353, 21416, 13452, 14008, 7262, 22233, 5454, 16303, 16634, 26303, 14256, 148, 11124, 12317, 4213, 27109, 24028, 29200, 21080, 21318, 16858, 24050, 24155, 31361, 15264, 11903, 3676,
29643, 26909, 14902, 3561, 28489, 24948, 1282, 13653, 30674, 2220, 5402, 6923, 3831, 19369, 3878, 20259, 19008, 22619, 23971, 30003, 21945, 9781, 26504, 12392, 32685, 25313, 6698, 5589, 12722, 5938, 19037, 6410,
31461, 6234, 12508, 9961, 3959, 6493, 1515, 25269, 24937, 28869, 58, 14700, 13971, 26264, 15117, 16215, 24555, 7815, 18330, 3039, 30212, 29288, 28082, 1954, 16085, 20710, 24484, 24774, 8380, 29815, 25951, 6541,
18115, 1679, 17110, 25898, 23073, 788, 23977, 18132, 29956, 28689, 26113, 10008, 12941, 15790, 1723, 21363, 28, 25184, 24778, 7200, 5071, 1885, 21974, 1071, 11333, 22867, 26153, 14295, 32168, 20825, 9676, 15629,
28650, 2598, 3309, 4693, 4686, 30080, 10116, 12249, 26667, 1528, 26679, 7864, 29421, 8405, 8826, 6816, 7516, 27726, 28666, 29087, 27681, 19964, 1340, 5686, 6021, 11662, 14721, 6064, 29309, 20415, 17902, 29873
};








unsigned int MAPSIZEX_hw, MAPSIZEY_hw, STARTX_hw, STARTY_hw;

//person popul_hw[POPULATION];

transformation popul_hw_t[POPULATION];


float          popul_hw_fitness[POPULATION];

float bestFitness_hw;
transformation bestTransformation_hw;
transformation old_hw;
transformation robotPose_hw;
transformation tr;

int flag_hw;
int flag2_hw;




inline unsigned int rand_hw_0() {
#pragma HLS INLINE
	static ap_uint<10> rand_index_0 = 0;
	unsigned int r;
	//	r = rand();
	//rand_index_0 = (rand_index_0 + 1) % RANND_MAX_SIZE;
	rand_index_0++;
	r = rand_matrix[rand_index_0];

	return r;
}


inline unsigned int rand_hw_1() {
#pragma HLS INLINE
	//static int rand_index_1 = 0;
	static ap_uint<10> rand_index_1 = 0;
	unsigned int r;
	//	r = rand();
	//rand_index_1 = (rand_index_1 + 1) % RANND_MAX_SIZE;
	rand_index_1++;
	r = rand_matrix[rand_index_1];

	return r;
}


inline unsigned int rand_hw_2() {
#pragma HLS INLINE
	//static int rand_index_2 = RANND_MAX_SIZE/4;
	static ap_uint<10> rand_index_2 = RANND_MAX_SIZE/4;
	unsigned int r;
	//	r = rand();
	//rand_index_2 = (rand_index_2 + 1) % RANND_MAX_SIZE;
	rand_index_2++;
	r = rand_matrix[rand_index_2];

	return r;
}

inline unsigned int rand_hw_3() {
#pragma HLS INLINE
	//static int rand_index_3 = RANND_MAX_SIZE/2;
	static ap_uint<10> rand_index_3 = RANND_MAX_SIZE/2;
	unsigned int r;
	//	r = rand();
	//rand_index_3 = (rand_index_3 + 1) % RANND_MAX_SIZE;
	rand_index_3++;
	r = rand_matrix_3[rand_index_3];

	return r;
}



inline void mutation(void){

	hls::stream<int>   ddx_fifo;
	hls::stream<int>   ddy_fifo;
	hls::stream<float> ddtheta_fifo;
	hls::stream<int>   k_fifo;

	for (unsigned int i = POPULATION / 2; i<POPULATION; i+=1){//mutation
		for (int d = 0; d < 5; d++) {
#pragma HLS PIPELINE
			int k = rand_hw_0() % POPULATION;
			int ddx = rand_hw_1() % DIASPORA / 2 - DIASPORA / 4;
			int ddy = rand_hw_2() % DIASPORA / 2 - DIASPORA / 4;
			float ddtheta= rand_hw_3() % 1000 / DIASPORAANGLE/2 - DIASPORAANGLEPLUS / 2;

			ddx_fifo << ddx;
			ddy_fifo << ddy;
			ddtheta_fifo << ddtheta;
			k_fifo << k;
		}
	}

	for (unsigned int i = POPULATION / 2; i<POPULATION; i+=1){//mutation
		for (int d = 0; d < 5; d++) {
	#pragma HLS PIPELINE
		int    k = k_fifo.read();
		int  ddx = ddx_fifo.read();
		int  ddy = ddy_fifo.read();
		int  ddtheta = ddtheta_fifo.read();

		if (popul_hw_fitness[k]>popul_hw_fitness[i]){
			popul_hw_t[i].dx = ddx;
			popul_hw_t[i].dy = ddy;
			popul_hw_t[i].theta = ddtheta;
		}
	}
}


}

inline void fixNewGeneration_hw(void){
#pragma HLS DATAFLOW
//#pragma HLS ARRAY_PARTITION variable=popul_hw_fitness complete dim=1
//#pragma HLS ARRAY_PARTITION variable=popul_hw_t       complete dim=1

	popul_hw_t[0].dx = bestTransformation_hw.dx;//elitism
	popul_hw_t[0].dy = bestTransformation_hw.dy;
	popul_hw_t[0].theta = bestTransformation_hw.theta;

	unsigned int k, l;

	for (unsigned int i = 1; i<POPULATION / 2; i++){//elitism 2, me std 20 kalo
#pragma HLS PIPELINE
		if ( i<POPULATION / 4)
			tr = bestTransformation_hw;
		else
			tr = old_hw;

		popul_hw_t[i].dx = (tr.dx) + rand_hw_1() % DIASPORA / 2 - DIASPORA / 4;
		popul_hw_t[i].dy = (tr.dy) + rand_hw_2() % DIASPORA / 2 - DIASPORA / 4;
		popul_hw_t[i].theta = (tr.theta) + rand_hw_3() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}

	mutation();
/*
	for (unsigned int i = POPULATION / 2; i<POPULATION; i+=1){//mutation
		for (int d = 0; d < 5; d++) {
#pragma HLS PIPELINE
			k = rand_hw_0() % POPULATION;

			if (popul_hw_fitness[k]>popul_hw_fitness[i]){
				popul_hw_t[i].dx = popul_hw_t[k].dx + rand_hw_1() % DIASPORA / 2 - DIASPORA / 4;
				popul_hw_t[i].dy = popul_hw_t[k].dy + rand_hw_2() % DIASPORA / 2 - DIASPORA / 4;
				popul_hw_t[i].theta = popul_hw_t[k].theta + (rand_hw_3() % 16384);// / DIASPORAANGLE/2 - DIASPORAANGLEPLUS / 2;

			}
		}
	}
	*/
}



void updateFitnesses_hw(
		unsigned char map_hw[MAX_SCAN*MAX_SCAN],
		int   original_hw_p_x[LASERRAYS],
		int   original_hw_p_y[LASERRAYS]){
#pragma HLS DATAFLOW
	int tempx, tempy;
	unsigned int i;
	float sinth, costh;
	float tttx, ttty;
	transformation temp;


	hls::stream<float> sinth_fifo;
	hls::stream<float> costh_fifo;
	hls::stream<int> temp_dx_fifo;
	hls::stream<int> temp_dy_fifo;



	int temp_dx_local;
	int temp_dy_local;

	float tmp_fitness = 0;
	hls::stream<float> tmp_fitness_fifo;
	hls::stream<float> fitness_fifo;
	hls::stream<unsigned int> fitness_fifo_index;


	hls::stream<transformation> popul_hw_t_fifo_1;
	hls::stream<transformation> popul_hw_t_fifo_2;
	hls::stream<transformation> popul_hw_t_fifo_3;
	hls::stream<transformation> popul_hw_t_fifo_4;


	for (i = 0; i<POPULATION; i++)	{
#pragma HLS PIPELINE II=1

		temp.dx = robotPose_hw.dx + popul_hw_t[i].dx;
		temp.dy = robotPose_hw.dy + popul_hw_t[i].dy;
		temp.theta = robotPose_hw.theta + popul_hw_t[i].theta;

		//float _sin, _cos;
		//sin_cos(temp.theta, &_sin,  &_cos);
		sinth_fifo << hls::sin(temp.theta);
		costh_fifo << hls::cos(temp.theta);

		temp_dx_fifo << temp.dx;
		temp_dy_fifo << temp.dy;

		popul_hw_t_fifo_1 << popul_hw_t[i];
	}

	for (i = 0; i<POPULATION; i++)	{
		for (unsigned int j = 0; j<LASERRAYS; j += ANAPOSO){
#pragma HLS PIPELINE  II=1
			if (j==0) {
				costh = costh_fifo.read();
				sinth = sinth_fifo.read();
				temp_dx_local = temp_dx_fifo.read();
				temp_dy_local = temp_dy_fifo.read();
				popul_hw_t_fifo_2 << popul_hw_t_fifo_1.read();
			}


			tempx = original_hw_p_x[j];
			tempy = original_hw_p_y[j];

			tttx = tempx*costh - tempy*sinth + temp_dx_local;
			ttty = tempx*sinth + tempy*costh + temp_dy_local;

			tttx += STARTX_hw;
			ttty += STARTY_hw;
//			fitness_fifo  << (255 - map_hw[(unsigned int)tttx*MAX_SCAN+(unsigned int)ttty]) / 255.0;
			fitness_fifo_index << (unsigned int)tttx*MAX_SCAN+(unsigned int)ttty;
		}
	}

	for (i = 0; i<POPULATION; i++)	{
		for (unsigned int j = 0; j<LASERRAYS; j += ANAPOSO){
#pragma HLS PIPELINE  II=1
			if (j==0) {
				popul_hw_t_fifo_3 << popul_hw_t_fifo_2.read();
			}
			fitness_fifo  << (255 - map_hw[fitness_fifo_index.read()]) / 255.0;
		}
	}



	for (i = 0; i<POPULATION; i++)	{
		for (unsigned int j = 0; j<LASERRAYS; j += 4*ANAPOSO){
#pragma HLS PIPELINE  II=1
			float fitness_1;
			float fitness_2;
			float fitness_3;
			float fitness_4;
			float fitness_5;
			fitness_1 = fitness_fifo.read();
			if (j+1<LASERRAYS)
				fitness_2 = fitness_fifo.read();
			else
				fitness_2 = 0;
			if (j+2<LASERRAYS)
				fitness_3 = fitness_fifo.read();
			else
				fitness_3 = 0;

			if (j+3<LASERRAYS)
				fitness_4 = fitness_fifo.read();
			else
				fitness_4 = 0;

//			if (j+4<LASERRAYS)
//				fitness_5 = fitness_fifo.read();
//			else
//				fitness_5 = 0;

			float tmp =fitness_1 + fitness_2 + fitness_3 + fitness_4 + fitness_5;

			if (j==0) {
				tmp_fitness = 0;
				popul_hw_t_fifo_4 << popul_hw_t_fifo_3.read();
			}

			tmp_fitness  += tmp;

			if (j+4*ANAPOSO >= LASERRAYS)
				tmp_fitness_fifo << tmp_fitness;
		}
	}

	for (i = 0; i<POPULATION; i++)	{
#pragma HLS PIPELINE  II=1
		float local_fitness = tmp_fitness_fifo.read();
		popul_hw_fitness[i] =local_fitness;
		transformation popul_hw_t_local = popul_hw_t_fifo_4.read();

		if (bestFitness_hw < local_fitness){
			bestFitness_hw = local_fitness;
			bestTransformation_hw = popul_hw_t_local;
			if ((bestTransformation_hw.theta<0.2 && bestTransformation_hw.theta>-0.2)){
				flag_hw = 1;  //0.2
			}
			else { flag_hw = 0; }
		}
	}


}



inline void initialisePopulation_hw(void){
	//		srand_hw(time(0));
	MAPSIZEX_hw = MAPSIZEY_hw = 400;//724;
	STARTX_hw = STARTY_hw = 100;//362;

	if (bestTransformation_hw.theta>0.15 || bestTransformation_hw.theta<-0.15){
		popul_hw_t[0].dx = 0;
		popul_hw_t[0].dy = 0;
		popul_hw_t[0].theta = 0;
		flag2_hw = 0;
	}
	else{
		popul_hw_t[0].dx = rand_hw_1() % DIASPORA - DIASPORA / 2;
		popul_hw_t[0].dy = rand_hw_2() % DIASPORA - DIASPORA / 2;
		popul_hw_t[0].theta = rand_hw_3() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
		flag2_hw = 1;
	}
	for (unsigned int i = 1; i<POPULATION; i++){
#pragma HLS PIPELINE
		popul_hw_t[i].dx = rand_hw_1() % DIASPORA - DIASPORA / 2;
		popul_hw_t[i].dy = rand_hw_2() % DIASPORA - DIASPORA / 2;
		popul_hw_t[i].theta = rand_hw_3() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}
}


void runIteration_hw(
	unsigned char             map_sw[MAX_SCAN*MAX_SCAN],
	//u64             map_sw[MAX_SCAN*MAX_SCAN/8],

	int            *robotPose_dx,
	int            *robotPose_dy,
	float          *robotPose_theta,
	int            *bestTransformation_dx,
	int            *bestTransformation_dy,
	float          *bestTransformation_theta,

	int            *old_sw_dx,
	int            *old_sw_dy,
	float          *old_sw_theta,

	int             p_x[LASERRAYS],
	int             p_y[LASERRAYS]
	){


#pragma HLS INTERFACE s_axilite port=return bundle=bus_control

#pragma HLS INTERFACE s_axilite port=map_sw bundle=bus_control
#pragma HLS INTERFACE s_axilite port=p_x    bundle=bus_control
#pragma HLS INTERFACE s_axilite port=p_y    bundle=bus_control

#pragma HLS INTERFACE s_axilite port=robotPose_dx             bundle=bus_control
#pragma HLS INTERFACE s_axilite port=robotPose_dy             bundle=bus_control
#pragma HLS INTERFACE s_axilite port=robotPose_theta          bundle=bus_control
#pragma HLS INTERFACE s_axilite port=bestTransformation_dx    bundle=bus_control
#pragma HLS INTERFACE s_axilite port=bestTransformation_dy    bundle=bus_control
#pragma HLS INTERFACE s_axilite port=bestTransformation_theta bundle=bus_control
#pragma HLS INTERFACE s_axilite port=old_sw_dx bundle=        bus_control
#pragma HLS INTERFACE s_axilite port=old_sw_dy bundle=        bus_control
#pragma HLS INTERFACE s_axilite port=old_sw_theta bundle=     bus_control


#pragma HLS INTERFACE m_axi depth=1024 port=map_sw bundle=gemm_1
#pragma HLS INTERFACE m_axi depth=1024 port=p_x    bundle=gemm_2
#pragma HLS INTERFACE m_axi depth=1024 port=p_y    bundle=gemm_3

	unsigned char map_hw[MAX_SCAN*MAX_SCAN];
#pragma HLS ARRAY_PARTITION variable=map_hw cyclic factor=8 dim=1
	int   original_hw_p_x[LASERRAYS];
	int   original_hw_p_y[LASERRAYS];

	initialisePopulation_hw();
	robotPose_hw.dx = *robotPose_dx;
	robotPose_hw.dy = *robotPose_dy;
	robotPose_hw.theta = *robotPose_theta;

	bestTransformation_hw.dx = *bestTransformation_dx;
	bestTransformation_hw.dy = *bestTransformation_dy;
	bestTransformation_hw.theta = *bestTransformation_theta;

	old_hw.dx = *old_sw_dx;
	old_hw.dy = *old_sw_dy;
	old_hw.theta = *old_sw_theta;


//	WIDE_DATA_TYPE tmp;
	for (unsigned int i = 0; i<MAX_SCAN*MAX_SCAN/8; i+=1) {
#pragma HLS PIPELINE
		map_hw[i] = map_sw[i];
//		tmp.data = map_sw[i];
//		for (int j = 0; j < 8; j++)
//			map_hw[i*8+j] = tmp.unsigned_char_data.a[j];
	}
	for (int i = 0; i < LASERRAYS; i++) {
#pragma HLS PIPELINE
		original_hw_p_x[i] = p_x[i];
		original_hw_p_y[i] = p_y[i];
	}

	for (int i = 0; i < 19; i++) {
		bestFitness_hw = 0;
		bestTransformation_hw.dx = bestTransformation_hw.dy = bestTransformation_hw.theta = 0;

		updateFitnesses_hw(map_hw, original_hw_p_x, original_hw_p_y);
		fixNewGeneration_hw();
	}


	*robotPose_dx = robotPose_hw.dx;
	*robotPose_dy = robotPose_hw.dy;
	*robotPose_theta = robotPose_hw.theta;

	*bestTransformation_dx = bestTransformation_hw.dx;
	*bestTransformation_dy = bestTransformation_hw.dy;
	*bestTransformation_theta = bestTransformation_hw.theta;

}


