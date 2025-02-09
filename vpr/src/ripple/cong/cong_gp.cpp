#include "cong_gp.h"
#include "lg/lg_main.h"
#include "gp/gp.h"
#include "cong_est_bb.h"
#include "prepack.h"
#include "pack.h"
#include "timing_info.h"
//#include "timing_reports.h"
#include "PreClusterDelayCalculator.h"
#include "PreClusterTimingGraphResolver.h"
#include "tatum/TimingReporter.hpp"
#include "vtr_error.h"

// #include "DebugNew.h"
// extern TracerNew NewTracer;

Legalizer* legalizer;
//******************************************up
// t_pack_molecule* TurnGroupsIntoMolecules(vector<Group>& groups,
//                                         std::multimap<AtomBlockId, t_pack_molecule*>& atom_molecules,
//                                         std::unordered_map<AtomBlockId, t_pb_graph_node*>& expected_lowest_cost_pb_gnode){
//     int num_blocks;
//     t_pack_molecule* list_of_molecules_head;
//     t_pack_molecule* cur_molecule;
//     cur_molecule = list_of_molecules_head = nullptr;
//     for(Group& group:groups){
//         num_blocks=group.instances.size();
//         cur_molecule = new t_pack_molecule;
//         cur_molecule->valid = true;
//         cur_molecule->type = (num_blocks>1) ? MOLECULE_TRANSFORMED_FROM_GROUP : MOLECULE_SINGLE_ATOM;
//         cur_molecule->atom_block_ids = std::vector<AtomBlockId>(num_blocks); //Initializes invalid
//         cur_molecule->num_blocks = num_blocks;
//         cur_molecule->root = 0;
//         for(int i=0; i<num_blocks; ++i){
//             Instance* &inst = group.instances[i];
//             cur_molecule->atom_block_ids[i]=inst->vpratomblkid;
//             atom_molecules.insert({inst->vpratomblkid, cur_molecule});
//             //cout<<Master::NameEnum2String(inst->master->name)<<"\t";
//         }
//         cur_molecule->next = list_of_molecules_head;
//         list_of_molecules_head = cur_molecule;
//         group.vpr_molecule=cur_molecule;
//         //cout<<endl;
//     }
//     //split molecule
//     // for(Group& group:groups){
//     //     for(int i=0; i<group.instances.size(); ++i){
//     //         AtomBlockId &blk_id=group.instances[i]->vpratomblkid;
//     //         cur_molecule = new t_pack_molecule;
//     //         cur_molecule->valid = true;
//     //         cur_molecule->type = MOLECULE_SINGLE_ATOM;
//     //         cur_molecule->atom_block_ids = std::vector<AtomBlockId>(1); //Initializes invalid
//     //         cur_molecule->num_blocks = 1;
//     //         cur_molecule->root = 0;
//     //         cur_molecule->atom_block_ids[0]=blk_id;
//     //         atom_molecules.insert({blk_id, cur_molecule});
//     //         cur_molecule->next = list_of_molecules_head;
//     //         list_of_molecules_head = cur_molecule;
//     //         group.instances[i]->vpr_molecule=cur_molecule;
//     //     }
//     // }
//     for (auto blk_id : g_vpr_ctx.atom().nlist.blocks()) {
//         t_pb_graph_node* best = get_expected_lowest_cost_primitive_for_atom_block(blk_id);
//         if (!best) {
//             /* Free the molecules in the linked list to avoid memory leakage */
//             cur_molecule = list_of_molecules_head;
//             while (cur_molecule) {
//                 t_pack_molecule* molecule_to_free = cur_molecule;
//                 cur_molecule = cur_molecule->next;
//                 delete molecule_to_free;
//             }
//             VPR_FATAL_ERROR(VPR_ERROR_PACK, "Failed to find any location to pack primitive of type '%s' in architecture",
//                             g_vpr_ctx.atom().nlist.block_model(blk_id)->name);
//         }
//         VTR_ASSERT_SAFE(nullptr != best);
//         expected_lowest_cost_pb_gnode[blk_id] = best;
//     }
//     return list_of_molecules_head;
// }
// //******************************************down
// void gp_cong(vector<Group>& groups, int iteration ) {
//     printlog(LOG_INFO, "");
//     printlog(LOG_INFO, " = = = = begin congestion-driven GP = = = = ");
//     printlog(LOG_INFO, "");
//     double prevHpwl, curHpwl, origHpwl;
//     // initial legalization
//     legalizer = new Legalizer(groups);
//     legalizer->Init(USE_VPR_CLB);
//
// //before do_clustering
// //******************************************up
//     t_packer_opts &packer_opts = database.vpr_setup->PackerOpts;
//     const t_analysis_opts& analysis_opts = database.vpr_setup->AnalysisOpts;
//     std::vector<t_lb_type_rr_node>* lb_type_rr_graphs=database.vpr_setup->PackerRRGraph;
//     std::unordered_set<AtomNetId> is_clock;
//     std::unordered_map<AtomBlockId, t_pb_graph_node*> expected_lowest_cost_pb_gnode;
//     std::unique_ptr<t_pack_molecule, decltype(&free_pack_molecules)> list_of_pack_molecules(nullptr, free_pack_molecules);
//     is_clock = alloc_and_load_is_clock(packer_opts.global_clocks);
//
//     list_of_pack_molecules.reset(TurnGroupsIntoMolecules(groups,
//                                                         database.atom_molecules,
//                                                         expected_lowest_cost_pb_gnode));
//     t_ext_pin_util_targets target_external_pin_util = parse_target_external_pin_util(packer_opts.target_external_pin_util);
//     t_pack_high_fanout_thresholds high_fanout_thresholds = parse_high_fanout_thresholds(packer_opts.high_fanout_threshold);
//     t_pack_molecule* molecule_head=list_of_pack_molecules.get();
//
//     // bool allow_unrelated_clustering = false;
//     // if (packer_opts->allow_unrelated_clustering == e_unrelated_clustering::ON) {
//     //     allow_unrelated_clustering = true;
//     // } else if (packer_opts->allow_unrelated_clustering == e_unrelated_clustering::OFF) {
//     //     allow_unrelated_clustering = false;
//     // }
//
//     bool balance_block_type_util = false;
//     if (packer_opts.balance_block_type_utilization == e_balance_block_type_util::ON) {
//         balance_block_type_util = true;
//     } else if (packer_opts.balance_block_type_utilization == e_balance_block_type_util::OFF) {
//         balance_block_type_util = false;
//     }
// //*******************************************down
//
// //in do_clustering , before while()
// //********************************************up
//     std::map<t_logical_block_type_ptr, size_t> num_used_type_instances;
//
//     t_cluster_placement_stats *cluster_placement_stats;
//     t_pb_graph_node** primitives_list;
//
//     auto& atom_ctx = g_vpr_ctx.atom();
//     auto& cluster_ctx = g_vpr_ctx.mutable_clustering();
//
//     vtr::vector<ClusterBlockId, std::vector<t_intra_lb_net>*> intra_lb_routing;
//
//     std::shared_ptr<PreClusterDelayCalculator> clustering_delay_calc;
//     std::shared_ptr<SetupTimingInfo> timing_info;
//
//     std::vector<int> le_count(3, 0);
//     int num_clb = 0;
//
//     vtr::vector<ClusterBlockId, std::vector<AtomNetId>> clb_inter_blk_nets(atom_ctx.nlist.blocks().size());
//
//     const t_molecule_stats max_molecule_stats = calc_max_molecules_stats(molecule_head);
//     mark_all_molecules_valid(molecule_head);
//     int num_molecules = count_molecules(molecule_head);
//
//     int cur_cluster_size,cur_pb_depth,max_cluster_size,max_pb_depth;
//     for (const auto& type : g_vpr_ctx.mutable_device().logical_block_types) {
//         if (is_empty_type(&type))
//             continue;
//
//         cur_cluster_size = get_max_primitives_in_pb_type(type.pb_type);
//         cur_pb_depth = get_max_depth_of_pb_type(type.pb_type);
//         if (cur_cluster_size > max_cluster_size) {
//             max_cluster_size = cur_cluster_size;
//         }
//         if (cur_pb_depth > max_pb_depth) {
//             max_pb_depth = cur_pb_depth;
//         }
//     }
//
//     alloc_and_init_clustering(max_molecule_stats,
//                               &cluster_placement_stats, &primitives_list, molecule_head,
//                               num_molecules);
//     auto primitive_candidate_block_types = identify_primitive_candidate_block_types();
//     // find the cluster type that has lut primitives
//     auto logic_block_type = identify_logic_block_type(primitive_candidate_block_types);
//     // find a LE pb_type within the found logic_block_type
//     auto le_pb_type = identify_le_block_type(logic_block_type);
//
//
//     if (packer_opts.timing_driven) {
//         /*
//          * Initialize the timing analyzer
//          */
//         clustering_delay_calc = std::make_shared<PreClusterDelayCalculator>(atom_ctx.nlist, atom_ctx.lookup, packer_opts.inter_cluster_net_delay, expected_lowest_cost_pb_gnode);
//         timing_info = make_setup_timing_info(clustering_delay_calc, packer_opts.timing_update_type);
//
//         //Calculate the initial timing
//         timing_info->update();
//
//         // if (isEchoFileEnabled(E_ECHO_PRE_PACKING_TIMING_GRAPH)) {
//         //     auto& timing_ctx = g_vpr_ctx.timing();
//         //     tatum::write_echo(getEchoFileName(E_ECHO_PRE_PACKING_TIMING_GRAPH),
//         //                       *timing_ctx.graph, *timing_ctx.constraints, *clustering_delay_calc, timing_info->analyzer());
//
//         //     tatum::NodeId debug_tnode = id_or_pin_name_to_tnode(analysis_opts.echo_dot_timing_graph_node);
//         //     write_setup_timing_graph_dot(getEchoFileName(E_ECHO_PRE_PACKING_TIMING_GRAPH) + std::string(".dot"),
//         //                                  *timing_info, debug_tnode);
//         // }
//
//         {
//             auto& timing_ctx = g_vpr_ctx.timing();
//             PreClusterTimingGraphResolver resolver(atom_ctx.nlist,
//                                                    atom_ctx.lookup, *timing_ctx.graph, *clustering_delay_calc);
//             resolver.set_detail_level(analysis_opts.timing_report_detail);
//
//             tatum::TimingReporter timing_reporter(resolver, *timing_ctx.graph,
//                                                   *timing_ctx.constraints);
//
//             timing_reporter.report_timing_setup(
//                 "pre_pack.report_timing.setup.rpt",
//                 *timing_info->setup_analyzer(),
//                 analysis_opts.timing_report_npaths);
//         }
//
//     }
//
//
// //******************************************down
//     legalizer->RunAll(  SITE_HPWL_SMALL_WIN, DEFAULT,packer_opts,lb_type_rr_graphs,database.atom_molecules,
//                         primitives_list,max_cluster_size,&cluster_ctx.clb_nlist,
//                         num_used_type_instances,is_clock,high_fanout_thresholds,timing_info,
//                         target_external_pin_util,intra_lb_routing,clb_inter_blk_nets,logic_block_type,
//                         le_pb_type,le_count,num_clb,primitive_candidate_block_types,
//                         balance_block_type_util,cluster_placement_stats);
//     /****************************************************************
//      * Free Data Structures (after while in do_clustering)
//      *****************************************************************/
//     if((int)cluster_ctx.clb_nlist.blocks().size() != num_clb){
//         printlog(LOG_ERROR, "intra_lb_routing.size() != num_clb");
//     }
//     check_clustering();
//     ////output_clustering(intra_lb_routing, packer_opts.global_clocks, is_clock, arch->architecture_id, packer_opts.output_file.c_str(), false);
//     VTR_ASSERT(cluster_ctx.clb_nlist.blocks().size() == intra_lb_routing.size());
//     for (auto blk_id : cluster_ctx.clb_nlist.blocks())
//         free_intra_lb_nets(intra_lb_routing[blk_id]);
//
//     intra_lb_routing.clear();
//
//     free_cluster_placement_stats(cluster_placement_stats);
//
//     for (auto blk_id : cluster_ctx.clb_nlist.blocks())
//         cluster_ctx.clb_nlist.remove_block(blk_id);
//
//     cluster_ctx.clb_nlist = ClusteredNetlist();
//
//     free(unclustered_list_head);//check whethere unclustered_list_head is given value in alloc_and_init_clustering()
//     free(memory_pool);//same as up
//
//     free(primitives_list);
//
//
//
//     //******************************************************************
//     legalizer->GetResult(NO_UPDATE);
//     origHpwl = curHpwl = database.getHPWL();
//     printlog(LOG_INFO, "**************");
//
//     for (int iter = 0; iter < iteration; iter++) {
//         // inflate
//         AdjAreaByCong(groups);
//
//         // gp again
//         gplace(groups);
//
//         // legalize
//         legalizer->Init(USE_VPR_CLB);
//         legalizer->RunAll(SITE_HPWL_SMALL_WIN, DEFAULT);
//         legalizer->GetResult(NO_UPDATE);
//         prevHpwl = curHpwl;
//         curHpwl = database.getHPWL();
//
//         printlog(LOG_INFO, "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =");
//         printlog(LOG_INFO,
//                  "iter %d: prev_WL=%0f, cur_WL=%0f, delta=%.2lf%%",
//                  iter,
//                  prevHpwl,
//                  curHpwl,
//                  (curHpwl / prevHpwl - 1) * 100.0);
//         printlog(LOG_INFO, "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =");
//     }
//     printlog(LOG_INFO, "");
//     printlog(LOG_INFO, " = = = = finish congestion-driven GP = = = = ");
//     printlog(LOG_INFO,
//              "Totally, orig_WL=%0f, cur_WL=%0f, delta=%.2lf%%",
//              origHpwl,
//              curHpwl,
//              (curHpwl / origHpwl - 1) * 100.0);
//     CongEstBB cong;
//     cong.Run();
//     WriteMap("cong_final", cong.siteDemand);
//
//     delete legalizer;
// }
void gp_cong(vector<Group>& groups, int iteration) {
    printlog(LOG_INFO, "");
    printlog(LOG_INFO, " = = = = begin congestion-driven GP = = = = ");
    printlog(LOG_INFO, "");
    double prevHpwl, curHpwl, origHpwl;

    // initial legalization
    legalizer = new Legalizer(groups);
    legalizer->Init(USE_VPR_CLB);
    legalizer->RunAll(SITE_HPWL_SMALL_WIN, DEFAULT);
    legalizer->GetResult(NO_UPDATE);
    origHpwl = curHpwl = database.getHPWL();
    printlog(LOG_INFO, "**************");

    //delete &NewTracer;

    for (int iter = 0; iter < iteration; iter++) {
        // inflate
        AdjAreaByCong(groups);

        // gp again
        gplace(groups);

        // legalize
        legalizer->Init(USE_VPR_CLB);
        legalizer->RunAll(SITE_HPWL_SMALL_WIN, DEFAULT);
        legalizer->GetResult(NO_UPDATE);
        prevHpwl = curHpwl;
        curHpwl = database.getHPWL();

        printlog(LOG_INFO, "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =");
        printlog(LOG_INFO,
                 "iter %d: prev_WL=%0f, cur_WL=%0f, delta=%.2lf%%",
                 iter,
                 prevHpwl,
                 curHpwl,
                 (curHpwl / prevHpwl - 1) * 100.0);
        printlog(LOG_INFO, "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =");
    }
    printlog(LOG_INFO, "");
    printlog(LOG_INFO, " = = = = finish congestion-driven GP = = = = ");
    printlog(LOG_INFO,
             "Totally, orig_WL=%0f, cur_WL=%0f, delta=%.2lf%%",
             origHpwl,
             curHpwl,
             (curHpwl / origHpwl - 1) * 100.0);
    CongEstBB cong;
    cong.Run();
    WriteMap("cong_final", cong.siteDemand);

    delete legalizer;
}

void GetBleDispMap(vector<Group>& groups, vector<vector<double>>& bleDispMap) {
    bleDispMap.resize(database.sitemap_nx, vector<double>(database.sitemap_ny, 0.0));
    for (int x = 0; x < database.sitemap_nx; x++)
        for (int y = 0; y < database.sitemap_ny; y++)
            if (database.sites[x][y]->pack != NULL && database.sites[x][y]->type->name == SiteType::SLICE) {
                unsigned num = 0;
                for (auto gid : legalizer->lgData.groupMap[x][y]) {
                    if (groups[gid].instances[0]->IsLUTFF()) {
                        ++num;
                        bleDispMap[x][y] += legalizer->lgData.dispPerGroup[gid];
                    }
                }
                if (num != 0) bleDispMap[x][y] /= num;
            }
}

void AdjAreaByCong(vector<Group>& groups) {
    CongEstBB cong;
    cong.Run();
    static int cnt = 0;
    WriteMap("cong_iter" + to_string(cnt++), cong.siteDemand);
    int nScaleUp = 0, nScaleDown = 0, nLargeDisp = 0;
    double maxAreaScale = 1.0, minAreaScale = 1.0;

    // only consider sites with bles
    vector<Point2<int>> sites;
    for (int x = 0; x < database.sitemap_nx; x++)
        for (int y = 0; y < database.sitemap_ny; y++)
            if (database.sites[x][y]->pack != NULL && cong.siteDemand[x][y] > cong.minDem) {
                bool ble = false;
                for (auto gid : legalizer->lgData.groupMap[x][y]) {
                    if (groups[gid].instances[0]->IsLUTFF()) {
                        ble = true;
                        break;
                    }
                }
                if (ble) sites.emplace_back(x, y);
            }
    function<double(Point2<int>)> get_demand = [&](const Point2<int> s) { return cong.siteDemand[s.x()][s.y()]; };
    ComputeAndSort(sites, get_demand, less<double>());

    // inflate (also handle large disp?)
    for (unsigned i = sites.size() - 1; i > 0.9 * sites.size(); --i) {
        int x = sites[i].x();
        int y = sites[i].y();
        if (cong.siteDemand[x][y] < 360) break;
        nScaleUp++;
        for (auto gid : legalizer->lgData.groupMap[x][y]) {
            if (!groups[gid].instances[0]->IsLUTFF()) continue;
            groups[gid].areaScale *= 1.2;
            if (groups[gid].areaScale > maxAreaScale) maxAreaScale = groups[gid].areaScale;
        }
    }

    // shrink
    // vector<vector<double>> bleDispMap;
    // GetBleDispMap(groups, bleDispMap);
    for (unsigned i = 0; i < 0.3 * sites.size(); ++i) {
        int x = sites[i].x();
        int y = sites[i].y();
        if (cong.siteDemand[x][y] > 180) break;
        // if (bleDispMap[x][y] > 0.5){
        if (legalizer->lgData.dispPerSite[x][y] > 2) {
            ++nLargeDisp;
            continue;
        }
        nScaleDown++;
        for (auto gid : legalizer->lgData.groupMap[x][y]) {
            if (!groups[gid].instances[0]->IsLUTFF()) continue;
            groups[gid].areaScale *= 0.8;
            if (groups[gid].areaScale < minAreaScale) minAreaScale = groups[gid].areaScale;
        }
    }

    printlog(LOG_INFO,
             "#site: %d, #up: %d, #down: %d, #large disp: %d, max as: %.2lf, min as: %.2lf",
             sites.size(),
             nScaleUp,
             nScaleDown,
             nLargeDisp,
             maxAreaScale,
             minAreaScale);
}