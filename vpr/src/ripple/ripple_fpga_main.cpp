#include "db/db.h"
using namespace db;
#include "gp/gp.h"
#include "pack/ripple_pack.h"
#include "lg/lg.h"
#include "dp/dp.h"
#include "cong/cong.h"

//#include "../base/globals.h"
#include "globals.h"

Setting setting;

//bool get_args(int argc, char** argv);

//int main(int argc, char** argv) {
bool ripple_fpga_main(t_vpr_setup* vpr_setup_in,t_arch* arch) {
    // init_log(LOG_ALL);
    init_log(LOG_NORMAL);

    log() << "-----------------------------------" << endl;
    log() << "             RippleFPGA            " << endl;
    log() << "  Chinese University of Hong Kong  " << endl;
    log() << "-----------------------------------" << endl;
    //if (!get_args(argc, argv)) return 1;
    //database.readAux(setting.io_aux);
    //database.readLib(setting.io_lib);
    //database.readNodes(setting.io_nodes);
    //database.readScl(setting.io_scl);
    //database.readPl(setting.io_pl);
    //database.readNets(setting.io_nets);

    database.vpr_setup=vpr_setup_in;
    database.arch=arch;
    //database.readArch();
    database.read_from_vpr_database();

    database.setup();
    database.print();

    gpSetting.init();

    vector<Group> groups(database.instances.size());
    for (unsigned int i = 0; i < groups.size(); i++) {
        groups[i].instances.push_back(database.instances[i]);
        groups[i].id = i;
    }

    // for(auto grouptemp:groups){
    //     for (auto instancetemp:grouptemp.instances){
    //         if(instancetemp->id==0){
    //             cout<<"here"<<endl;
    //         }
    //     }
    // }
    // reallocate
    gpSetting.set0();
    gplace(groups);
    ReallocByCluster(groups);

    // pack bles
    gpSetting.set1();
    gplace(groups);
    packble(groups);



    // for(auto grouptemp:groups){
    //     for (auto instancetemp:grouptemp.instances){
    //         if(instancetemp->id==0){
    //             cout<<"here"<<endl;
    //         }
    //     }
    // }

    // gp with bles
    database.setuppackvar(groups);

    gpSetting.set2();
    gplace(groups);
    if (database.crmap_nx == 0) {
        gpSetting.set2c();
        gp_cong(groups, 1);//change 3 to 1
    }
    legalize_partial(groups);
    gpSetting.set3();
    gplace(groups);

    // legalize
    // planning(groups);            ////////// delete by jia 
    legalize_partial(groups);    ////////// delete by jia 
    if (database.crmap_nx == 0)
        legalize(groups, SITE_HPWL, UPDATE_XY_ORDER);
    else
        legalize(groups, SITE_HPWL_SMALL_WIN, UPDATE_XY_ORDER);
    dplace(groups,1);//change 10(default) to 1

    //database.writePl(setting.io_out);

    printlog(LOG_INFO, "hpwl = %.1lf", database.getHPWL(true));
    printlog(LOG_INFO, "#net = %d / %d", database.getRouteNet(), database.nets.size());

    database.draw("cells.png", Database::DrawInstances);
    database.freepackvar();

    log() << "-----------------------------------" << endl;
    log() << "    RippleFPGA terminating...      " << endl;
    log() << "-----------------------------------" << endl;
    return true;
}

bool get_args(int argc, char** argv) {
    bool valid = true;
    for (int a = 1; a < argc; a++) {
        if (strcmp(argv[a], "-out") == 0) {
            setting.io_out.assign(argv[++a]);
            unsigned pos = setting.io_out.find_last_of('.');
            database.bmName = setting.io_out.substr(0, pos);
        } else if (strcmp(argv[a], "-aux") == 0) {
            setting.io_aux.assign(argv[++a]);
        } else {
            cerr << "unknown parameter: " << argv[a] << endl;
            valid = false;
        }
    }
    if (valid && setting.io_aux == "") valid = false;
    if (!valid) log() << "usage: " << argv[0] << " -aux <aux_file> [-out <output_file>]" << endl;
    return valid;
}
