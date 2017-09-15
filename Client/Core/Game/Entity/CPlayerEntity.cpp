/*
* Copyright (C) GTA-Network Team
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

#include "CPlayerEntity.h"
#include "CVehicleEntity.h"

#include <Game/eGame.h>
#include <Game/EFLC/CPad.h>
#include <Game/EFLC/CScript.h>
#include <Game/EFLC/CModelManager.h>
#include <Game/EFLC/CVehicle.h>
#include <Game/EFLC/CTask.h>
#include <Game/EFLC/IVTasks.h>
#include <Game/EFLC/CPedTaskManager.h>
#include <Math/CMaths.h>
#include <Ptrs.h>


DWORD dwPlayerModelHashes[] = 
{
	EFLC::CScript::MODEL_PLAYER, EFLC::CScript::MODEL_M_Y_MULTIPLAYER, EFLC::CScript::MODEL_F_Y_MULTIPLAYER, EFLC::CScript::MODEL_SUPERLOD,
	EFLC::CScript::MODEL_IG_ANNA, EFLC::CScript::MODEL_IG_ANTHONY, EFLC::CScript::MODEL_IG_BADMAN, EFLC::CScript::MODEL_IG_BERNIE_CRANE,
	EFLC::CScript::MODEL_IG_BLEDAR, EFLC::CScript::MODEL_IG_BRIAN, EFLC::CScript::MODEL_IG_BRUCIE, EFLC::CScript::MODEL_IG_BULGARIN,
	EFLC::CScript::MODEL_IG_CHARISE, EFLC::CScript::MODEL_IG_CHARLIEUC, EFLC::CScript::MODEL_IG_CLARENCE, EFLC::CScript::MODEL_IG_DARDAN,
	EFLC::CScript::MODEL_IG_DARKO, EFLC::CScript::MODEL_IG_DERRICK_MC, EFLC::CScript::MODEL_IG_DMITRI, EFLC::CScript::MODEL_IG_DWAYNE,
	EFLC::CScript::MODEL_IG_EDDIELOW, EFLC::CScript::MODEL_IG_FAUSTIN, EFLC::CScript::MODEL_IG_FRANCIS_MC, EFLC::CScript::MODEL_IG_FRENCH_TOM,
	EFLC::CScript::MODEL_IG_GORDON, EFLC::CScript::MODEL_IG_GRACIE, EFLC::CScript::MODEL_IG_HOSSAN, EFLC::CScript::MODEL_IG_ILYENA, EFLC::CScript::MODEL_IG_ISAAC,
	EFLC::CScript::MODEL_IG_IVAN, EFLC::CScript::MODEL_IG_JAY, EFLC::CScript::MODEL_IG_JASON, EFLC::CScript::MODEL_IG_JEFF, EFLC::CScript::MODEL_IG_JIMMY,
	EFLC::CScript::MODEL_IG_JOHNNYBIKER, EFLC::CScript::MODEL_IG_KATEMC, EFLC::CScript::MODEL_IG_KENNY, EFLC::CScript::MODEL_IG_LILJACOB,
	EFLC::CScript::MODEL_IG_LILJACOBW, EFLC::CScript::MODEL_IG_LUCA, EFLC::CScript::MODEL_IG_LUIS, EFLC::CScript::MODEL_IG_MALLORIE, EFLC::CScript::MODEL_IG_MAMC,
	EFLC::CScript::MODEL_IG_MANNY, EFLC::CScript::MODEL_IG_MARNIE, EFLC::CScript::MODEL_IG_MEL, EFLC::CScript::MODEL_IG_MICHAEL, EFLC::CScript::MODEL_IG_MICHELLE,
	EFLC::CScript::MODEL_IG_MICKEY, EFLC::CScript::MODEL_IG_PACKIE_MC, EFLC::CScript::MODEL_IG_PATHOS, EFLC::CScript::MODEL_IG_PETROVIC,
	EFLC::CScript::MODEL_IG_PHIL_BELL, EFLC::CScript::MODEL_IG_PLAYBOY_X, EFLC::CScript::MODEL_IG_RAY_BOCCINO, EFLC::CScript::MODEL_IG_RICKY,
	EFLC::CScript::MODEL_IG_ROMAN, EFLC::CScript::MODEL_IG_ROMANW, EFLC::CScript::MODEL_IG_SARAH, EFLC::CScript::MODEL_IG_TUNA, EFLC::CScript::MODEL_IG_VINNY_SPAZ,
	EFLC::CScript::MODEL_IG_VLAD, EFLC::CScript::MODEL_M_Y_GAFR_LO_01, EFLC::CScript::MODEL_M_Y_GAFR_LO_02, EFLC::CScript::MODEL_M_Y_GAFR_HI_01,
	EFLC::CScript::MODEL_M_Y_GAFR_HI_02, EFLC::CScript::MODEL_M_Y_GALB_LO_01, EFLC::CScript::MODEL_M_Y_GALB_LO_02, EFLC::CScript::MODEL_M_Y_GALB_LO_03,
	EFLC::CScript::MODEL_M_Y_GALB_LO_04, EFLC::CScript::MODEL_M_M_GBIK_LO_03, EFLC::CScript::MODEL_M_Y_GBIK_HI_01, EFLC::CScript::MODEL_M_Y_GBIK_HI_02,
	EFLC::CScript::MODEL_M_Y_GBIK02_LO_02, EFLC::CScript::MODEL_M_Y_GBIK_LO_01, EFLC::CScript::MODEL_M_Y_GBIK_LO_02, EFLC::CScript::MODEL_M_Y_GIRI_LO_01,
	EFLC::CScript::MODEL_M_Y_GIRI_LO_02, EFLC::CScript::MODEL_M_Y_GIRI_LO_03, EFLC::CScript::MODEL_M_M_GJAM_HI_01, EFLC::CScript::MODEL_M_M_GJAM_HI_02,
	EFLC::CScript::MODEL_M_M_GJAM_HI_03, EFLC::CScript::MODEL_M_Y_GJAM_LO_01, EFLC::CScript::MODEL_M_Y_GJAM_LO_02, EFLC::CScript::MODEL_M_Y_GKOR_LO_01,
	EFLC::CScript::MODEL_M_Y_GKOR_LO_02, EFLC::CScript::MODEL_M_Y_GLAT_LO_01, EFLC::CScript::MODEL_M_Y_GLAT_LO_02, EFLC::CScript::MODEL_M_Y_GLAT_HI_01,
	EFLC::CScript::MODEL_M_Y_GLAT_HI_02, EFLC::CScript::MODEL_M_Y_GMAF_HI_01, EFLC::CScript::MODEL_M_Y_GMAF_HI_02, EFLC::CScript::MODEL_M_Y_GMAF_LO_01,
	EFLC::CScript::MODEL_M_Y_GMAF_LO_02, EFLC::CScript::MODEL_M_O_GRUS_HI_01, EFLC::CScript::MODEL_M_Y_GRUS_LO_01, EFLC::CScript::MODEL_M_Y_GRUS_LO_02,
	EFLC::CScript::MODEL_M_Y_GRUS_HI_02, EFLC::CScript::MODEL_M_M_GRU2_HI_01, EFLC::CScript::MODEL_M_M_GRU2_HI_02, EFLC::CScript::MODEL_M_M_GRU2_LO_02,
	EFLC::CScript::MODEL_M_Y_GRU2_LO_01, EFLC::CScript::MODEL_M_M_GTRI_HI_01, EFLC::CScript::MODEL_M_M_GTRI_HI_02, EFLC::CScript::MODEL_M_Y_GTRI_LO_01,
	EFLC::CScript::MODEL_M_Y_GTRI_LO_02, EFLC::CScript::MODEL_F_O_MAID_01, EFLC::CScript::MODEL_F_O_BINCO, EFLC::CScript::MODEL_F_Y_BANK_01, EFLC::CScript::MODEL_F_Y_DOCTOR_01,
	EFLC::CScript::MODEL_F_Y_GYMGAL_01, EFLC::CScript::MODEL_F_Y_FF_BURGER_R, EFLC::CScript::MODEL_F_Y_FF_CLUCK_R, EFLC::CScript::MODEL_F_Y_FF_RSCAFE,
	EFLC::CScript::MODEL_F_Y_FF_TWCAFE, EFLC::CScript::MODEL_F_Y_FF_WSPIZZA_R, EFLC::CScript::MODEL_F_Y_HOOKER_01, EFLC::CScript::MODEL_F_Y_HOOKER_03,
	EFLC::CScript::MODEL_F_Y_NURSE, EFLC::CScript::MODEL_F_Y_STRIPPERC01, EFLC::CScript::MODEL_F_Y_STRIPPERC02, EFLC::CScript::MODEL_F_Y_WAITRESS_01,
	EFLC::CScript::MODEL_M_M_ALCOHOLIC, EFLC::CScript::MODEL_M_M_ARMOURED, EFLC::CScript::MODEL_M_M_BUSDRIVER, EFLC::CScript::MODEL_M_M_CHINATOWN_01,
	EFLC::CScript::MODEL_M_M_CRACKHEAD, EFLC::CScript::MODEL_M_M_DOC_SCRUBS_01, EFLC::CScript::MODEL_M_M_DOCTOR_01, EFLC::CScript::MODEL_M_M_DODGYDOC,
	EFLC::CScript::MODEL_M_M_EECOOK, EFLC::CScript::MODEL_M_M_ENFORCER, EFLC::CScript::MODEL_M_M_FACTORY_01, EFLC::CScript::MODEL_M_M_FATCOP_01,
	EFLC::CScript::MODEL_M_M_FBI, EFLC::CScript::MODEL_M_M_FEDCO, EFLC::CScript::MODEL_M_M_FIRECHIEF, EFLC::CScript::MODEL_M_M_GUNNUT_01, EFLC::CScript::MODEL_M_M_HELIPILOT_01,
	EFLC::CScript::MODEL_M_M_HPORTER_01, EFLC::CScript::MODEL_M_M_KOREACOOK_01, EFLC::CScript::MODEL_M_M_LAWYER_01, EFLC::CScript::MODEL_M_M_LAWYER_02,
	EFLC::CScript::MODEL_M_M_LOONYBLACK, EFLC::CScript::MODEL_M_M_PILOT, EFLC::CScript::MODEL_M_M_PINDUS_01, EFLC::CScript::MODEL_M_M_POSTAL_01,
	EFLC::CScript::MODEL_M_M_SAXPLAYER_01, EFLC::CScript::MODEL_M_M_SECURITYMAN, EFLC::CScript::MODEL_M_M_SELLER_01, EFLC::CScript::MODEL_M_M_SHORTORDER,
	EFLC::CScript::MODEL_M_M_STREETFOOD_01, EFLC::CScript::MODEL_M_M_SWEEPER, EFLC::CScript::MODEL_M_M_TAXIDRIVER, EFLC::CScript::MODEL_M_M_TELEPHONE,
	EFLC::CScript::MODEL_M_M_TENNIS, EFLC::CScript::MODEL_M_M_TRAIN_01, EFLC::CScript::MODEL_M_M_TRAMPBLACK, EFLC::CScript::MODEL_M_M_TRUCKER_01,
	EFLC::CScript::MODEL_M_O_JANITOR, EFLC::CScript::MODEL_M_O_HOTEL_FOOT, EFLC::CScript::MODEL_M_O_MPMOBBOSS, EFLC::CScript::MODEL_M_Y_AIRWORKER,
	EFLC::CScript::MODEL_M_Y_BARMAN_01, EFLC::CScript::MODEL_M_Y_BOUNCER_01, EFLC::CScript::MODEL_M_Y_BOUNCER_02, EFLC::CScript::MODEL_M_Y_BOWL_01,
	EFLC::CScript::MODEL_M_Y_BOWL_02, EFLC::CScript::MODEL_M_Y_CHINVEND_01, EFLC::CScript::MODEL_M_Y_CLUBFIT, EFLC::CScript::MODEL_M_Y_CONSTRUCT_01,
	EFLC::CScript::MODEL_M_Y_CONSTRUCT_02, EFLC::CScript::MODEL_M_Y_CONSTRUCT_03, EFLC::CScript::MODEL_M_Y_COP, EFLC::CScript::MODEL_M_Y_COP_TRAFFIC,
	EFLC::CScript::MODEL_M_Y_COURIER, EFLC::CScript::MODEL_M_Y_COWBOY_01, EFLC::CScript::MODEL_M_Y_DEALER, EFLC::CScript::MODEL_M_Y_DRUG_01,
	EFLC::CScript::MODEL_M_Y_FF_BURGER_R, EFLC::CScript::MODEL_M_Y_FF_CLUCK_R, EFLC::CScript::MODEL_M_Y_FF_RSCAFE, EFLC::CScript::MODEL_M_Y_FF_TWCAFE,
	EFLC::CScript::MODEL_M_Y_FF_WSPIZZA_R, EFLC::CScript::MODEL_M_Y_FIREMAN, EFLC::CScript::MODEL_M_Y_GARBAGE, EFLC::CScript::MODEL_M_Y_GOON_01,
	EFLC::CScript::MODEL_M_Y_GYMGUY_01, EFLC::CScript::MODEL_M_Y_MECHANIC_02, EFLC::CScript::MODEL_M_Y_MODO, EFLC::CScript::MODEL_M_Y_NHELIPILOT,
	EFLC::CScript::MODEL_M_Y_PERSEUS, EFLC::CScript::MODEL_M_Y_PINDUS_01, EFLC::CScript::MODEL_M_Y_PINDUS_02, EFLC::CScript::MODEL_M_Y_PINDUS_03, 
	EFLC::CScript::MODEL_M_Y_PMEDIC, EFLC::CScript::MODEL_M_Y_PRISON, EFLC::CScript::MODEL_M_Y_PRISONAOM, EFLC::CScript::MODEL_M_Y_ROMANCAB, EFLC::CScript::MODEL_M_Y_RUNNER,
	EFLC::CScript::MODEL_M_Y_SHOPASST_01, EFLC::CScript::MODEL_M_Y_STROOPER, EFLC::CScript::MODEL_M_Y_SWAT, EFLC::CScript::MODEL_M_Y_SWORDSWALLOW,
	EFLC::CScript::MODEL_M_Y_THIEF, EFLC::CScript::MODEL_M_Y_VALET, EFLC::CScript::MODEL_M_Y_VENDOR, EFLC::CScript::MODEL_M_Y_FRENCHTOM, EFLC::CScript::MODEL_M_Y_JIM_FITZ,
	EFLC::CScript::MODEL_F_O_PEASTEURO_01, EFLC::CScript::MODEL_F_O_PEASTEURO_02, EFLC::CScript::MODEL_F_O_PHARBRON_01, EFLC::CScript::MODEL_F_O_PJERSEY_01,
	EFLC::CScript::MODEL_F_O_PORIENT_01, EFLC::CScript::MODEL_F_O_RICH_01, EFLC::CScript::MODEL_F_M_BUSINESS_01, EFLC::CScript::MODEL_F_M_BUSINESS_02,
	EFLC::CScript::MODEL_F_M_CHINATOWN, EFLC::CScript::MODEL_F_M_PBUSINESS, EFLC::CScript::MODEL_F_M_PEASTEURO_01, EFLC::CScript::MODEL_F_M_PHARBRON_01,
	EFLC::CScript::MODEL_F_M_PJERSEY_01, EFLC::CScript::MODEL_F_M_PJERSEY_02, EFLC::CScript::MODEL_F_M_PLATIN_01, EFLC::CScript::MODEL_F_M_PLATIN_02,
	EFLC::CScript::MODEL_F_M_PMANHAT_01, EFLC::CScript::MODEL_F_M_PMANHAT_02, EFLC::CScript::MODEL_F_M_PORIENT_01, EFLC::CScript::MODEL_F_M_PRICH_01,
	EFLC::CScript::MODEL_F_Y_BUSINESS_01, EFLC::CScript::MODEL_F_Y_CDRESS_01, EFLC::CScript::MODEL_F_Y_PBRONX_01, EFLC::CScript::MODEL_F_Y_PCOOL_01,
	EFLC::CScript::MODEL_F_Y_PCOOL_02, EFLC::CScript::MODEL_F_Y_PEASTEURO_01, EFLC::CScript::MODEL_F_Y_PHARBRON_01, EFLC::CScript::MODEL_F_Y_PHARLEM_01,
	EFLC::CScript::MODEL_F_Y_PJERSEY_02, EFLC::CScript::MODEL_F_Y_PLATIN_01, EFLC::CScript::MODEL_F_Y_PLATIN_02, EFLC::CScript::MODEL_F_Y_PLATIN_03,
	EFLC::CScript::MODEL_F_Y_PMANHAT_01, EFLC::CScript::MODEL_F_Y_PMANHAT_02, EFLC::CScript::MODEL_F_Y_PMANHAT_03, EFLC::CScript::MODEL_F_Y_PORIENT_01,
	EFLC::CScript::MODEL_F_Y_PQUEENS_01, EFLC::CScript::MODEL_F_Y_PRICH_01, EFLC::CScript::MODEL_F_Y_PVILLBO_02, EFLC::CScript::MODEL_F_Y_SHOP_03,
	EFLC::CScript::MODEL_F_Y_SHOP_04, EFLC::CScript::MODEL_F_Y_SHOPPER_05, EFLC::CScript::MODEL_F_Y_SOCIALITE, EFLC::CScript::MODEL_F_Y_STREET_02,
	EFLC::CScript::MODEL_F_Y_STREET_05, EFLC::CScript::MODEL_F_Y_STREET_09, EFLC::CScript::MODEL_F_Y_STREET_12, EFLC::CScript::MODEL_F_Y_STREET_30,
	EFLC::CScript::MODEL_F_Y_STREET_34, EFLC::CScript::MODEL_F_Y_TOURIST_01, EFLC::CScript::MODEL_F_Y_VILLBO_01, EFLC::CScript::MODEL_M_M_BUSINESS_02,
	EFLC::CScript::MODEL_M_M_BUSINESS_03, EFLC::CScript::MODEL_M_M_EE_HEAVY_01, EFLC::CScript::MODEL_M_M_EE_HEAVY_02, EFLC::CScript::MODEL_M_M_FATMOB_01,
	EFLC::CScript::MODEL_M_M_GAYMID, EFLC::CScript::MODEL_M_M_GENBUM_01, EFLC::CScript::MODEL_M_M_LOONYWHITE, EFLC::CScript::MODEL_M_M_MIDTOWN_01,
	EFLC::CScript::MODEL_M_M_PBUSINESS_01, EFLC::CScript::MODEL_M_M_PEASTEURO_01, EFLC::CScript::MODEL_M_M_PHARBRON_01, EFLC::CScript::MODEL_M_M_PINDUS_02,
	EFLC::CScript::MODEL_M_M_PITALIAN_01, EFLC::CScript::MODEL_M_M_PITALIAN_02, EFLC::CScript::MODEL_M_M_PLATIN_01, EFLC::CScript::MODEL_M_M_PLATIN_02,
	EFLC::CScript::MODEL_M_M_PLATIN_03, EFLC::CScript::MODEL_M_M_PMANHAT_01, EFLC::CScript::MODEL_M_M_PMANHAT_02, EFLC::CScript::MODEL_M_M_PORIENT_01,
	EFLC::CScript::MODEL_M_M_PRICH_01, EFLC::CScript::MODEL_M_O_EASTEURO_01, EFLC::CScript::MODEL_M_O_HASID_01, EFLC::CScript::MODEL_M_O_MOBSTER,
	EFLC::CScript::MODEL_M_O_PEASTEURO_02, EFLC::CScript::MODEL_M_O_PHARBRON_01, EFLC::CScript::MODEL_M_O_PJERSEY_01, EFLC::CScript::MODEL_M_O_STREET_01,
	EFLC::CScript::MODEL_M_O_SUITED, EFLC::CScript::MODEL_M_Y_BOHO_01, EFLC::CScript::MODEL_M_Y_BOHOGUY_01, EFLC::CScript::MODEL_M_Y_BRONX_01,
	EFLC::CScript::MODEL_M_Y_BUSINESS_01, EFLC::CScript::MODEL_M_Y_BUSINESS_02, EFLC::CScript::MODEL_M_Y_CHINATOWN_03, EFLC::CScript::MODEL_M_Y_CHOPSHOP_01,
	EFLC::CScript::MODEL_M_Y_CHOPSHOP_02, EFLC::CScript::MODEL_M_Y_DODGY_01, EFLC::CScript::MODEL_M_Y_DORK_02, EFLC::CScript::MODEL_M_Y_DOWNTOWN_01, 
	EFLC::CScript::MODEL_M_Y_DOWNTOWN_02, EFLC::CScript::MODEL_M_Y_DOWNTOWN_03, EFLC::CScript::MODEL_M_Y_GAYYOUNG, EFLC::CScript::MODEL_M_Y_GENSTREET_11, 
	EFLC::CScript::MODEL_M_Y_GENSTREET_16, EFLC::CScript::MODEL_M_Y_GENSTREET_20, EFLC::CScript::MODEL_M_Y_GENSTREET_34, EFLC::CScript::MODEL_M_Y_HARDMAN_01,
	EFLC::CScript::MODEL_M_Y_HARLEM_01, EFLC::CScript::MODEL_M_Y_HARLEM_02, EFLC::CScript::MODEL_M_Y_HARLEM_04, EFLC::CScript::MODEL_M_Y_HASID_01,
	EFLC::CScript::MODEL_M_Y_LEASTSIDE_01, EFLC::CScript::MODEL_M_Y_PBRONX_01, EFLC::CScript::MODEL_M_Y_PCOOL_01, EFLC::CScript::MODEL_M_Y_PCOOL_02, 
	EFLC::CScript::MODEL_M_Y_PEASTEURO_01, EFLC::CScript::MODEL_M_Y_PHARBRON_01, EFLC::CScript::MODEL_M_Y_PHARLEM_01, EFLC::CScript::MODEL_M_Y_PJERSEY_01,
	EFLC::CScript::MODEL_M_Y_PLATIN_01, EFLC::CScript::MODEL_M_Y_PLATIN_02, EFLC::CScript::MODEL_M_Y_PLATIN_03, EFLC::CScript::MODEL_M_Y_PMANHAT_01,
	EFLC::CScript::MODEL_M_Y_PMANHAT_02, EFLC::CScript::MODEL_M_Y_PORIENT_01, EFLC::CScript::MODEL_M_Y_PQUEENS_01, EFLC::CScript::MODEL_M_Y_PRICH_01,
	EFLC::CScript::MODEL_M_Y_PVILLBO_01, EFLC::CScript::MODEL_M_Y_PVILLBO_02, EFLC::CScript::MODEL_M_Y_PVILLBO_03, EFLC::CScript::MODEL_M_Y_QUEENSBRIDGE,
	EFLC::CScript::MODEL_M_Y_SHADY_02, EFLC::CScript::MODEL_M_Y_SKATEBIKE_01, EFLC::CScript::MODEL_M_Y_SOHO_01, EFLC::CScript::MODEL_M_Y_STREET_01,
	EFLC::CScript::MODEL_M_Y_STREET_03, EFLC::CScript::MODEL_M_Y_STREET_04, EFLC::CScript::MODEL_M_Y_STREETBLK_02, EFLC::CScript::MODEL_M_Y_STREETBLK_03,
	EFLC::CScript::MODEL_M_Y_STREETPUNK_02, EFLC::CScript::MODEL_M_Y_STREETPUNK_04, EFLC::CScript::MODEL_M_Y_STREETPUNK_05, EFLC::CScript::MODEL_M_Y_TOUGH_05,
	EFLC::CScript::MODEL_M_Y_TOURIST_02, EFLC::CScript::F_Y_BIKESTRIPPER_01, EFLC::CScript::F_Y_BUSIASIAN, EFLC::CScript::F_Y_EMIDTOWN_01, 
	EFLC::CScript::F_Y_GANGELS_01, EFLC::CScript::F_Y_GANGELS_02, EFLC::CScript::F_Y_GANGELS_03, EFLC::CScript::F_Y_GLOST_01,
	EFLC::CScript::F_Y_GLOST_02, EFLC::CScript::F_Y_GLOST_03, EFLC::CScript::F_Y_GLOST_04, EFLC::CScript::F_Y_GRYDERS_01, 
	EFLC::CScript::F_Y_UPTOWN_01, EFLC::CScript::F_Y_UPTOWN_CS, EFLC::CScript::IG_ASHLEYA, EFLC::CScript::IG_BILLY,
	EFLC::CScript::IG_BILLYPRISON, EFLC::CScript::IG_BRIANJ, EFLC::CScript::IG_CLAY, EFLC::CScript::IG_DAVE_GROSSMAN,
	EFLC::CScript::IG_DESEAN, EFLC::CScript::IG_EVAN, EFLC::CScript::IG_JASON_M, EFLC::CScript::IG_JIM_FITZ,
	EFLC::CScript::IG_LOSTGIRL, EFLC::CScript::IG_MALC, EFLC::CScript::IG_MARTA, EFLC::CScript::IG_MATTHEWS, 
	EFLC::CScript::IG_MCCORNISH, EFLC::CScript::IG_NIKO, EFLC::CScript::IG_PGIRL_01, EFLC::CScript::IG_PGIRL_02,
	EFLC::CScript::IG_ROMAN_E1, EFLC::CScript::IG_STROOPER, EFLC::CScript::IG_TERRY, EFLC::CScript::LOSTBUDDY_01,
	EFLC::CScript::LOSTBUDDY_02, EFLC::CScript::LOSTBUDDY_03, EFLC::CScript::LOSTBUDDY_04, EFLC::CScript::LOSTBUDDY_05,
	EFLC::CScript::LOSTBUDDY_06, EFLC::CScript::LOSTBUDDY_07, EFLC::CScript::LOSTBUDDY_08, EFLC::CScript::LOSTBUDDY_09,
	EFLC::CScript::LOSTBUDDY_10, EFLC::CScript::LOSTBUDDY_11, EFLC::CScript::LOSTBUDDY_12, EFLC::CScript::LOSTBUDDY_13,
	EFLC::CScript::M_M_SMARTBLACK, EFLC::CScript::M_M_SPRETZER, EFLC::CScript::M_M_UPEAST_01, EFLC::CScript::M_M_UPTOWN_01,
	EFLC::CScript::M_O_HISPANIC_01, EFLC::CScript::M_Y_BIKEMECH, EFLC::CScript::M_Y_BUSIASIAN, EFLC::CScript::M_Y_BUSIMIDEAST,
	EFLC::CScript::M_Y_CIADLC_01, EFLC::CScript::M_Y_CIADLC_02, EFLC::CScript::M_Y_DOORMAN_01, EFLC::CScript::M_Y_GANGELS_02,
	EFLC::CScript::M_Y_GANGELS_03, EFLC::CScript::M_Y_GANGELS_04, EFLC::CScript::M_Y_GANGELS_05, EFLC::CScript::M_Y_GANGELS_06,
	EFLC::CScript::M_Y_GAYGANG_01, EFLC::CScript::M_Y_GLOST_01, EFLC::CScript::M_Y_GLOST_02, EFLC::CScript::M_Y_GLOST_03,
	EFLC::CScript::M_Y_GLOST_04, EFLC::CScript::M_Y_GLOST_05, EFLC::CScript::M_Y_GLOST_06, EFLC::CScript::M_Y_GRYDERS_01,
	EFLC::CScript::M_Y_GRYDERS_02, EFLC::CScript::M_Y_GTRI_02, EFLC::CScript::M_Y_GTRIAD_HI_01, EFLC::CScript::M_Y_HIP_02,
	EFLC::CScript::M_Y_HIPMALE_01, EFLC::CScript::M_Y_HISPANIC_01, EFLC::CScript::M_Y_PRISONBLACK, EFLC::CScript::M_Y_PRISONDLC_01,
	EFLC::CScript::M_Y_PRISONGUARD, EFLC::CScript::F_Y_ASIANCLUB_01, EFLC::CScript::F_Y_ASIANCLUB_02, EFLC::CScript::F_Y_CLOEPARKER,
	EFLC::CScript::F_Y_CLUBEURO_01, EFLC::CScript::F_Y_DANCER_01, EFLC::CScript::F_Y_DOMGIRL_01, EFLC::CScript::F_Y_EMIDTOWN_02,
	EFLC::CScript::F_Y_HOSTESS, EFLC::CScript::F_Y_HOTCHICK_01, EFLC::CScript::F_Y_HOTCHICK_02, EFLC::CScript::F_Y_HOTCHICK_03,
	EFLC::CScript::F_Y_JONI, EFLC::CScript::F_Y_PGIRL_01, EFLC::CScript::F_Y_PGIRL_02, EFLC::CScript::F_Y_SMID_01, 
	EFLC::CScript::F_Y_TRENDY_01, EFLC::CScript::IG_AHMAD, EFLC::CScript::IG_ARMANDO, EFLC::CScript::IG_ARMSDEALER,
	EFLC::CScript::IG_ARNAUD, EFLC::CScript::IG_BANKER, EFLC::CScript::IG_BLUEBROS, EFLC::CScript::IG_BRUCIE2,
	EFLC::CScript::IG_BULGARIN2, EFLC::CScript::IG_DAISY, EFLC::CScript::IG_DEEJAY, EFLC::CScript::IG_DESSIE,
	EFLC::CScript::IG_GRACIE2, EFLC::CScript::IG_HENRIQUE, EFLC::CScript::IG_ISSAC2, EFLC::CScript::IG_JACKSON,
	EFLC::CScript::IG_JOHNNY2, EFLC::CScript::IG_LUIS2, EFLC::CScript::IG_MARGOT, EFLC::CScript::IG_MORI_K,
	EFLC::CScript::IG_MR_SANTOS, EFLC::CScript::IG_NAPOLI, EFLC::CScript::IG_OYVEY, EFLC::CScript::IG_ROCCO,
	EFLC::CScript::IG_ROYAL, EFLC::CScript::IG_SPADE, EFLC::CScript::IG_TAHIR, EFLC::CScript::IG_TIMUR,
	EFLC::CScript::IG_TONY, EFLC::CScript::IG_TRAMP2, EFLC::CScript::IG_TRIAD, EFLC::CScript::IG_TROY,
	EFLC::CScript::IG_VIC, EFLC::CScript::IG_VICGIRL, EFLC::CScript::IG_VINCE, EFLC::CScript::IG_YUSEF,
	EFLC::CScript::M_M_E2MAF_01, EFLC::CScript::M_M_E2MAF_02, EFLC::CScript::M_M_MAFUNION, EFLC::CScript::M_Y_AMIRGUARD_01,
	EFLC::CScript::M_Y_BARMAISON, EFLC::CScript::M_Y_BATHROOM, EFLC::CScript::M_Y_CELEBBLOG, EFLC::CScript::M_Y_CLUBBLACK_01, 
	EFLC::CScript::M_Y_CLUBEURO_01, EFLC::CScript::M_Y_CLUBEURO_02, EFLC::CScript::M_Y_CLUBEURO_03, EFLC::CScript::M_Y_CLUBWHITE_01,
	EFLC::CScript::M_Y_DOMDRUG_01, EFLC::CScript::M_Y_DOMGUY_01, EFLC::CScript::M_Y_DOMGUY_02, EFLC::CScript::M_Y_DOORMAN_02,
	EFLC::CScript::M_Y_E2RUSSIAN_01, EFLC::CScript::M_Y_E2RUSSIAN_02, EFLC::CScript::M_Y_E2RUSSIAN_03, EFLC::CScript::M_Y_EXSPORTS,
	EFLC::CScript::M_Y_FIGHTCLUB_01, EFLC::CScript::M_Y_FIGHTCLUB_02, EFLC::CScript::M_Y_FIGHTCLUB_03, EFLC::CScript::M_Y_FIGHTCLUB_04,
	EFLC::CScript::M_Y_FIGHTCLUB_05, EFLC::CScript::M_Y_FIGHTCLUB_06, EFLC::CScript::M_Y_FIGHTCLUB_07, EFLC::CScript::M_Y_FIGHTCLUB_08,
	EFLC::CScript::M_Y_GAYBLACK_01, EFLC::CScript::M_Y_GAYDANCER, EFLC::CScript::M_Y_GAYGENERAL_01, EFLC::CScript::M_Y_GAYWHITE_01,
	EFLC::CScript::M_Y_GUIDO_01, EFLC::CScript::M_Y_GUIDO_02, EFLC::CScript::M_Y_MIDEAST_01, EFLC::CScript::M_Y_MOBPARTY,
	EFLC::CScript::M_Y_PAPARAZZI_01, EFLC::CScript::M_Y_UPTOWN_01
};

DWORD SkinIdToModelHash(int modelid)
{
	if(modelid >= 0 || modelid < sizeof(dwPlayerModelHashes))
		return dwPlayerModelHashes[modelid];

	return 0x00;
}

CPlayerEntity::CPlayerEntity(bool bLocalPlayer) :
	CNetworkEntity(PLAYER_ENTITY), 
	m_iWantedLevel(0), 
	m_bLocalPlayer(bLocalPlayer),
	m_usPlayerId(INVALID_ENTITY_ID), 
	m_usPing(0), 
	m_bNetworked(false),
	m_uiColor(0xFFFFFFFF), 
	m_bSpawned(false), 
	m_pPlayerPed(nullptr),
	m_pPlayerInfo(nullptr),
	m_bytePlayerNumber(INVALID_PLAYER_PED), 
	m_pContextData(nullptr),
	m_pVehicle(nullptr),
	m_byteSeat(0)
{
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(INVALID_PLAYER_PED);
	memset(&m_lastControlState, NULL, sizeof(CControlState));
	memset(&m_ControlState, NULL, sizeof(CControlState));

	m_LastSyncPacket.matrix.vecPosition = CVector3();

	// Initialize & Reset all stuff(classes,structs)
	m_pVehicleEnterExit = new sPlayerEntity_VehicleData;

	ResetVehicleEnterExit();

	// Is this the localplayer?
	if(IsLocalPlayer())
	{
		// Set the localplayer CScript handle
		m_bytePlayerNumber = (BYTE)g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex();

		// Create a new player ped instance
		m_pPlayerPed = new EFLC::CPlayerPed(g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(m_bytePlayerNumber)->m_pPlayerPed);

		// Get the localplayer info pointer
		m_pPlayerInfo = new EFLC::CPlayerInfo(g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(m_bytePlayerNumber));

		// Create a new context data instance with the local player info
		m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

		// Set the context data player ped pointer
		m_pContextData->SetPlayerPed(m_pPlayerPed);

		m_pPlayerWeapons = new CPlayerWeapons(m_pPlayerPed->GetPedWeapons());

		// Add our model reference
		m_pModelInfo->AddReference(false);

		// Set the localplayer name
		// ViruZz: We're setting the nick that the client has in his settings, if not you're just setting it to NULL and we don't want that.
		SetNick(CVAR_GET_STRING("nick").Get());

		// Mark as spawned
		m_bSpawned = true;

		CLogFile::Printf("LOCALPLAYER: m_bytePlayerNumber: %d, m_pPlayerPed: 0x%p, m_pPlayerInfo: 0x%p", m_bytePlayerNumber, m_pPlayerPed, m_pPlayerInfo);
	}
}

CPlayerEntity::~CPlayerEntity()
{
	// Is this not the localplayer?
	if(!IsLocalPlayer())
		Destroy();
}

unsigned short CPlayerEntity::GetPing()
{
	if(IsLocalPlayer())
	{
		//TODO: Get ping to current connected server.
		return -1;
	}
	else
		return m_usPing;
}

void CPlayerEntity::Pulse()
{
	// Is the player spawned?
	if(IsSpawned())
	{
		if(!IsLocalPlayer())
		{
			// Are we not in a vehicle?
			if(!IsInVehicle() && !HasVehicleEnterExit())
			{
				if (!IsJumping())
				{
					// Process interpolation
					Interpolate();
				}
			}
			if (HasVehicleEnterExit())
			{
				ProcessVehicleEnterExit();
			}
		}
	}
}

#include "Core\Game\EFLC\CPedFactory.h"

#define g_pPedFactory (*(EFLC::IPedFactoryNY**)((g_pCore->GetBase() + 0x156B764)))
#define sub_846CC0 ((void(__thiscall *)(EFLC::IPlayerInfo*, EFLC::IPed*))((g_pCore->GetBase() + 0x846CC0)))
#define CPedTaskManager__AssignPriorityTask ((void(__thiscall *) (EFLC::IPedTaskManager *, EFLC::ITask *, int, BYTE))((g_pCore->GetBase() + 0x9E3220)))
#define CTaskSimpleNetworkClone__CTaskSimpleNetworkClone ((EFLC::ITask *(__thiscall *) ())((g_pCore->GetBase() + 0x4FB940)))

#define sub_4FF7C0 ((WORD(__thiscall *)(void*))((g_pCore->GetBase() + 0x4FF7C0)))
#define dword_188CD50 (*(DWORD*)((g_pCore->GetBase() + 0x188CD50)))
#define sub_4FD0E0 ((bool(__thiscall *)(void*, void*))((g_pCore->GetBase() + 0x4FD0E0)))
#define dword_D4B0BC (*(DWORD*)((g_pCore->GetBase() + 0xD4B0BC)))

#pragma pack(push, 1)
struct SetupPedData
{
	DWORD field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	DWORD field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
	DWORD field_28;
	int field_2C;
	float fX;
	float fY;
	float fZ;
};
#pragma pack(pop)


bool CPlayerEntity::Create()
{
#if 0
	// Is this the localplayer or are we alread spawned?
	if (IsLocalPlayer() && IsSpawned())
		return false;

	m_pModelInfo->AddReference(true);

	m_bytePlayerNumber = (BYTE)g_pCore->GetGame()->GetPools()->FindFreePlayerInfoIndex();

	// Invalid player number?
	if (m_bytePlayerNumber == INVALID_PLAYER_PED)
		return false;

	// Create the player info instance
	m_pPlayerInfo = new EFLC::CPlayerInfo(m_bytePlayerNumber);

	// Create our context data
	m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

	// Set the game player info pointer
	g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(m_bytePlayerNumber, m_pPlayerInfo->GetPlayerInfo());

	WORD wPlayerData = MAKEWORD(m_bytePlayerNumber, 1);

	CVector3 vecPos;
	g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPos);

	SetupPedData spd;
	memset(&spd, 0, sizeof(SetupPedData));
	spd.field_0 = dword_D4B0BC;
	spd.field_8 = 0;
	spd.field_10 = 0;
	spd.field_14 = dword_D4B0BC;
	spd.field_20 = 0;
	spd.field_24 = 0;
	spd.field_28 = dword_D4B0BC;
	spd.fX = vecPos.fX;
	spd.fY = vecPos.fY;
	spd.fZ = vecPos.fZ;

	EFLC::IPlayerPed * pPlayerPed = (EFLC::IPlayerPed*)g_pPedFactory->CreatePlayerPed(&wPlayerData, m_pModelInfo->GetIndex(), m_bytePlayerNumber, (Matrix34*)&spd, false);

	// Ensure the ped was allocated
	if (!pPlayerPed)
		return false;

	sub_846CC0(m_pPlayerInfo->GetPlayerInfo(), pPlayerPed);

	EFLC::ITask * pCTaskSimpleNetworkClone = CTaskSimpleNetworkClone__CTaskSimpleNetworkClone();
	if (pCTaskSimpleNetworkClone)
		CPedTaskManager__AssignPriorityTask(&pPlayerPed->m_pPedIntelligence->m_pedTaskManager, pCTaskSimpleNetworkClone, 4, false);

	void* pNetObjPlayer = (void*)pPlayerPed->CreateNetworkObject(sub_4FF7C0(&dword_188CD50), 0, 0, 0, 32);
	sub_4FD0E0(&dword_188CD50, pNetObjPlayer);

	pPlayerPed->field_41 = 2;

	m_pPlayerPed = new EFLC::CPlayerPed(pPlayerPed);

	m_pPlayerInfo->SetPlayerPed(pPlayerPed);
	m_pPlayerPed->SetPlayerPed(pPlayerPed);

	m_pContextData->SetPlayerPed(m_pPlayerPed);

	m_pPlayerPed->AddToWorld();

	// Create the player blip
	EFLC::CScript::AddBlipForChar(GetScriptingHandle(), &m_uiBlip);
	EFLC::CScript::ChangeBlipNameFromAscii(m_uiBlip, m_strNick.Get());

	m_pPlayerWeapons = new CPlayerWeapons(m_pPlayerPed->GetPedWeapons());

	EFLC::CNativeInvoke::Invoke<unsigned int>(EFLC::CScript::NATIVE_SET_PLAYER_CONTROL_FOR_NETWORK, m_bytePlayerNumber, false, false);

	// Mark as spawned
	m_bSpawned = true;

	return true;

#else
	// Is this the localplayer or are we alread spawned?
	if (IsLocalPlayer() && IsSpawned())
		return false;

	// Add our model reference and load the model
	m_pModelInfo->AddReference(true);

	// Find a free player number
	m_bytePlayerNumber = (BYTE)g_pCore->GetGame()->GetPools()->FindFreePlayerInfoIndex();

	// Invalid player number?
	if (m_bytePlayerNumber == INVALID_PLAYER_PED)
		return false;

	// Create the player info instance
	m_pPlayerInfo = new EFLC::CPlayerInfo(m_bytePlayerNumber);

	// Create our context data
	m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

	// Set the game player info pointer
	g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(m_bytePlayerNumber, m_pPlayerInfo->GetPlayerInfo());

	// Allocate the player ped
	auto pPlayerPed = (EFLC::IPlayerPed *)g_pCore->GetGame()->GetPools()->GetPedPool()->Allocate();

	CLogFile::Printf("CREATE: m_bytePlayerNumber: %d, m_pPlayerInfo: 0x%p, pPlayerPed: 0x%p", m_bytePlayerNumber, m_pPlayerInfo, pPlayerPed);

	// Ensure the ped was allocated
	if (!pPlayerPed)
		return false;

	// Create the ped
	WORD wPlayerData = MAKEWORD(0, 1);
	((void(__thiscall*) (EFLC::IPed *, WORD*, int, unsigned int)) (COffsets::IV_Func__CreatePed))(pPlayerPed, &wPlayerData, m_pModelInfo->GetIndex(), m_bytePlayerNumber);

	// Setup the ped
	Matrix34 * pMatrix = nullptr;
	int iModelIndex = m_pModelInfo->GetIndex();
	_asm  push iModelIndex;
	_asm  push COffsets::IV_Var__PedFactory;
	_asm  mov edi, pMatrix;
	_asm  mov esi, pPlayerPed;
	_asm  call COffsets::IV_Func__SetupPed;

	// Set the player info
	m_pPlayerInfo->SetPlayerPed(pPlayerPed);

	// Set the player state to spawned
	m_pPlayerInfo->GetPlayerInfo()->m_dwState = 2;
	*(DWORD *)((char*)pPlayerPed + 0x260) |= 1u;

	// Set our player info with the ped
	pPlayerPed->m_pPlayerInfo = m_pPlayerInfo->GetPlayerInfo();

	// Create the player ped instance
	m_pPlayerPed = new EFLC::CPlayerPed(pPlayerPed);

	// Set the context data player ped pointer
	m_pContextData->SetPlayerPed(m_pPlayerPed);

	// Setup ped intelligence
	((void(__thiscall*) (EFLC::IPed *, BYTE)) (COffsets::IV_Func__SetupPedIntelligence))(pPlayerPed, 2);

	// Add to the world
	m_pPlayerPed->AddToWorld();

	// Create the player blip
	EFLC::CScript::AddBlipForChar(GetScriptingHandle(), &m_uiBlip);
	EFLC::CScript::ChangeBlipNameFromAscii(m_uiBlip, m_strNick.Get());

	EFLC::CTaskComplexPlayerOnFoot * pTask = new EFLC::CTaskComplexPlayerOnFoot();
	if (pTask)
		pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_DEFAULT);

	// Unfreeze the player
	EFLC::CNativeInvoke::Invoke<unsigned int>(EFLC::CScript::NATIVE_FREEZE_CHAR_POSITION, GetScriptingHandle(), false);

	// Disable head ik
	EFLC::CNativeInvoke::Invoke<unsigned int>(EFLC::CScript::NATIVE_BLOCK_CHAR_HEAD_IK, GetScriptingHandle(), true);

	// Disable shot los
	EFLC::CNativeInvoke::Invoke<unsigned int>(EFLC::CScript::NATIVE_SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS, GetScriptingHandle(), false);

	m_pPlayerWeapons = new CPlayerWeapons(m_pPlayerPed->GetPedWeapons());

	// Mark as spawned
	m_bSpawned = true;

#endif

	return true;
}

bool CPlayerEntity::Destroy()
{
	// Is this the localplayer?
	if(IsLocalPlayer())
		return false;

	// Is the player not spawned?
	if(!IsSpawned())
		return false;

	// Get the ped pointer
	EFLC::IPlayerPed * pPlayerPed = m_pPlayerPed->GetPlayerPed();

	// Deconstruct the ped intelligence
	((void(__thiscall*) (EFLC::IPedIntelligence *, BYTE)) (COffsets::IV_Func__ShutdownPedIntelligence))(pPlayerPed->m_pPedIntelligence, 0);

	*(DWORD *)((char*)pPlayerPed + 0x260) &= 0xFFFFFFFE;

	// Remove the ped from the world
	m_pPlayerPed->RemoveFromWorld();

	// Delete the player ped
	((void(__thiscall*) (EFLC::IPed *, BYTE)) (COffsets::IV_Func__DeletePed))(pPlayerPed, 1);

	// Remove the model reference
	m_pModelInfo->RemoveReference();

	// Do we have a valid context data record?
	if(m_pContextData)
	{
		// Delete the context data instance
		CContextDataManager::DestroyContextData(m_pContextData);

		// Invalidate the context data pointer
		m_pContextData = nullptr;
	}

	// Delete the player ped instance
	SAFE_DELETE(m_pPlayerPed);

	// Delete the player info instance
	SAFE_DELETE(m_pPlayerInfo);

	// Do we have a valid CScript handle?
	if(m_bytePlayerNumber != INVALID_PLAYER_PED)
	{
		// Reset the game player info pointer
		g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex((unsigned int) m_bytePlayerNumber, nullptr);

		// Invalidate the player number
		m_bytePlayerNumber = INVALID_PLAYER_PED;
	}

	// Mark as not spawned
	m_bSpawned = false;

	// Remove the blip
	EFLC::CScript::RemoveBlip(m_uiBlip);

	return true;
}

void CPlayerEntity::SetPosition(CVector3& vecPosition, bool bForce)
{
	// Are we spawned?
	if(IsSpawned())
		// Are we not in a vehicle and not entering a vehicle?
		if(!InternalIsInVehicle() && !HasVehicleEnterExit())
		{
			m_pPlayerPed->RemoveFromWorld();
			Vector4 coords(vecPosition.fX, vecPosition.fY, vecPosition.fZ, 0);
			m_pPlayerPed->GetPed()->SetCoordinates(&coords, 1, 0);
			m_pPlayerPed->GetPed()->UpdatePhysicsMatrix(true);
			m_pPlayerPed->AddToWorld();
		}

	// Just update the position
	if (bForce) 
		RemoveTargetPosition();

	CNetworkEntity::SetPosition(vecPosition);
}

void CPlayerEntity::GetPosition(CVector3& vecPosition)
{
	if (IsSpawned())
		m_pPlayerPed->GetPosition(vecPosition);
	else
		CNetworkEntity::GetPosition(vecPosition);
}

void CPlayerEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->SetMoveSpeed(vecMoveSpeed);

	CNetworkEntity::SetMoveSpeed(vecMoveSpeed);
}

void CPlayerEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->GetMoveSpeed(vecMoveSpeed);
	else
		vecMoveSpeed = CVector3();
}

void CPlayerEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->SetTurnSpeed(vecTurnSpeed);

	CNetworkEntity::SetTurnSpeed(vecTurnSpeed);
}

void CPlayerEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->GetTurnSpeed(vecTurnSpeed);
	else
		vecTurnSpeed = CVector3();
}

void CPlayerEntity::SetNick(const CString &strNick)
{
	m_strNick = strNick;
	CLogFile::Printf("Setting name to %s", strNick.Get());
}


void CPlayerEntity::SetColor(unsigned uiColor)
{
	assert(m_pPlayerInfo);

	// Save the colour
	m_uiColor = uiColor;

	// Do we have an active blip?
	if(m_uiBlip)
		EFLC::CScript::ChangeBlipColour(m_uiBlip, uiColor);

	m_pPlayerInfo->SetColour(uiColor);
}

unsigned CPlayerEntity::GetScriptingHandle()
{
	return g_pCore->GetGame()->GetPools()->GetPedPool()->HandleOf(m_pPlayerPed->GetPed());
}

void CPlayerEntity::SetHealth(float fHealth)
{
	EFLC::CScript::SetCharHealth(GetScriptingHandle(), fHealth + 100);
}

float CPlayerEntity::GetHealth()
{
	unsigned fHealth;
	EFLC::CScript::GetCharHealth(GetScriptingHandle(), &fHealth);
	return (float)fHealth;
}

void CPlayerEntity::SetArmour(float fnewArmour)
{
	if (IsSpawned())
	{
		unsigned int uiArmour;
		EFLC::CScript::GetCharArmour(GetScriptingHandle(), &uiArmour);
		EFLC::CScript::AddCharArmour(GetScriptingHandle(), fnewArmour - uiArmour);
	}
}

float CPlayerEntity::GetArmour()
{
	// Are we spawned?
    if(IsSpawned())
    {
        unsigned int uiArmour;
        EFLC::CScript::GetCharArmour(GetScriptingHandle(), &uiArmour);
        return uiArmour;
    }

    // Not spawned
    return 0;
}

void CPlayerEntity::SetRotation(CVector3& vecRotation)
{
	if (IsSpawned())
	{
		// Get the player matrix
		Matrix matMatrix;
		m_pPlayerPed->GetMatrix(matMatrix);

		// Convert the rotation from degrees to radians
		CVector3 vecNewRotation = Math::ConvertDegreesToRadians(vecRotation);

		// Apply the rotation to the vehicle matrix
		CGameFunction::ConvertEulerAnglesToRotationMatrix(vecNewRotation, matMatrix);

		// Set the new vehicle matrix
		m_pPlayerPed->SetMatrix(matMatrix);
	}

	CNetworkEntity::SetRotation(vecRotation);
}

void CPlayerEntity::GetRotation(CVector3& vecRotation)
{
	if (IsSpawned())
	{
		// Get the player matrix
		Matrix matMatrix;
		m_pPlayerPed->GetMatrix(matMatrix);

		// Convert the matrix to euler angles
		CVector3 vecNewRotation;
		CGameFunction::ConvertRotationMatrixToEulerAngles(matMatrix, vecNewRotation);

		// Flip the rotation
		vecNewRotation.fX = ((2 * PI) - vecNewRotation.fX);
		vecNewRotation.fY = ((2 * PI) - vecNewRotation.fY);
		vecNewRotation.fZ = ((2 * PI) - vecNewRotation.fZ);

		// Convert the rotation from radians to degrees
		vecRotation = Math::ConvertRadiansToDegrees(vecNewRotation);
	}
	else
		CNetworkEntity::GetRotation(vecRotation);
}


void CPlayerEntity::SetHeading(float fAngle)
{
	EFLC::IPed * pPed = m_pPlayerPed->GetPed();

	if(pPed)
		pPed->m_fCurrentHeading = fAngle;
}

float CPlayerEntity::GetHeading()
{
	EFLC::IPed * pPed = m_pPlayerPed->GetPed();

	if(pPed)
		return (pPed->m_fCurrentHeading);

	return 0.0f;
}

void CPlayerEntity::SetModel(int iModelId)
{
	// Get the model hash from skin id
	DWORD dwModelHash = SkinIdToModelHash(iModelId);

	if (dwModelHash == m_pModelInfo->GetHash())
		return;

	// Get the model index
	int iModelIndex = EFLC::CModelManager::GetModelIndexFromHash(dwModelHash);

	// Get the model info
	EFLC::CModelInfo * pModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

	m_pModelInfo->RemoveReference();
	m_pModelInfo = pModelInfo;

	if(IsSpawned())
	{
		// Add reference
		m_pModelInfo->AddReference(true);

		EFLC::CScript::GetCharDrawableVariation(GetScriptingHandle(), EFLC::CScript::ePedComponent::PED_COMPONENT_FACE);

		// change the model from the player
		EFLC::CScript::ChangePlayerModel(m_bytePlayerNumber,(EFLC::CScript::eModel)dwModelHash);

		m_pPlayerPed->SetPed(m_pPlayerInfo->GetPlayerPed());
	}
}

void CPlayerEntity::SetWantedLevel(int iWantedLevel)
{
	if (IsSpawned())
	{
		m_iWantedLevel = iWantedLevel;
		EFLC::CScript::SetFakeWantedLevel(iWantedLevel);
	}
}

int CPlayerEntity::GetWantedLevel()
{
	if (IsSpawned())
		return m_iWantedLevel;

	return 0;
}

void CPlayerEntity::SetControlState(CControlState * pControlState)
{
	// Is the player spawned?
	if(IsSpawned())
	{
		// Get the game pad
		EFLC::CPad * pPad = g_pCore->GetGame()->GetPad();

		// Is this not the localplayr?
		if(!IsLocalPlayer())
		{
			// Get the context data pad
			pPad = m_pContextData->GetPad();
		}

		// Set the last control state
		//pPad->SetLastControlState(m_ControlState);

		// Set the current control state
		pPad->SetCurrentControlState(*pControlState);
	}

	// Copy the current control state
	memcpy(&m_lastControlState, &m_ControlState, sizeof(CControlState));

	// Copy the control state
	memcpy(&m_ControlState, pControlState, sizeof(CControlState));
}

void CPlayerEntity::GetControlState(CControlState * pControlState)
{
	// Copy the current controls
	memcpy(pControlState, &m_ControlState, sizeof(CControlState));
}

void CPlayerEntity::GetLastControlState(CControlState * pControlState)
{
	// Copy the last controls
	memcpy(pControlState, &m_lastControlState, sizeof(CControlState));
}

void CPlayerEntity::InternalPutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Is the player spawned and not in a vehicle?
	if(IsSpawned() && !InternalIsInVehicle())
	{

		//if (IsSpawned() && !InternalIsInVehicle())
		//{
		//	// Get the door
		//	int iDoor = -2;

		//	if (byteSeat == 0)
		//		iDoor = 0;
		//	else if (byteSeat == 1)
		//		iDoor = 2;
		//	else if (byteSeat == 2)
		//		iDoor = 1;
		//	else if (byteSeat == 3)
		//		iDoor = 3;

		//	// Create the car set ped in vehicle task
		//	EFLC::CTaskSimpleCarSetPedInVehicle * pTask = new EFLC::CTaskSimpleCarSetPedInVehicle(pVehicle->GetGameVehicle(), iDoor, 0, 0);

		//	// Did the task create successfully?
		//	if (pTask)
		//	{
		//		// Process the ped
		//		pTask->ProcessPed(m_pPlayerPed);

		//		// Destroy the task
		//		pTask->Destroy();
		//	}
		//}

		//return;
		// Is this the driver seat?
		if(byteSeat == 0)
		{
			EFLC::CScript::WarpCharIntoCar(GetScriptingHandle(), pVehicle->GetScriptingHandle());
		}
		else
		{
			// Is the passenger seat valid?
			if(byteSeat <= pVehicle->GetMaxPassengers())
			{
				EFLC::CScript::WarpCharIntoCarAsPassenger(GetScriptingHandle(), pVehicle->GetScriptingHandle(), (byteSeat - 1));
			}
		}
	}
}

void CPlayerEntity::InternalRemoveFromVehicle()
{
	if (IsDead())
		return;

	// Are we spawned and in a vehicle?
	if(IsSpawned() && m_pVehicle)
	{
		// Create the car set ped out task
		EFLC::CTaskSimpleCarSetPedOut * pTask = new EFLC::CTaskSimpleCarSetPedOut(m_pVehicle->GetGameVehicle(), 0xF, 0, 1);

		// Was the task created?
		if(pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

bool CPlayerEntity::InternalIsInVehicle()
{
	// Are we spawned?
	if(IsSpawned())
		return (m_pPlayerPed->IsInVehicle());

	return false;
}

void CPlayerEntity::PutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Is the vehicle invalid?
	if(!pVehicle)
		return;

	// Are we already in a vehicle?
	if(IsInVehicle())
	{
		// Remove from the vehicle
		RemoveFromVehicle();
	}

	// Put the player in the vehicle
	InternalPutInVehicle(pVehicle, byteSeat);

	// Reset entry/exit
	ResetVehicleEnterExit();

	// Store the vehicle pointer
	m_pVehicle = pVehicle;

	// Store the seat
	m_byteSeat = byteSeat;

	// Set us in the vehicle
	m_pVehicle->SetOccupant(byteSeat, this);
}

void CPlayerEntity::RemoveFromVehicle()
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Are we not in a vehicle?
	if(!m_pVehicle)
		return;

	// Internally remove ourselfs from the vehicle
	InternalRemoveFromVehicle();

	// Reset the vehicle seat
	m_pVehicle->SetOccupant(m_byteSeat, nullptr);

	// Reset our vehicle pointer
	m_pVehicle = nullptr;

	// Reset our seat
	m_byteSeat = 0;

	// Reset entry/exit
	ResetVehicleEnterExit();
}

void CPlayerEntity::EnterVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Is the vehicle invalid?
	if(!pVehicle)
		return;

	// Are we already in a vehicle?
	if(IsInVehicle())
		return;

	// Create the enter vehicle task
	int iUnknown = -4;

	switch(byteSeat)
	{
	case 0: iUnknown = -7; break;
	case 1: iUnknown = 2; break;
	case 2: iUnknown = 1; break;
	case 3: iUnknown = 3; break;
	}

	unsigned int uiUnknown = 0;
	if(byteSeat > 0)
		uiUnknown = 0x200000;

	EFLC::CTaskComplexNewGetInVehicle * pTask = new EFLC::CTaskComplexNewGetInVehicle(pVehicle->GetGameVehicle(), iUnknown, 27, uiUnknown, -2.0f);

	// Did the task get created?
	if(pTask)
	{
		// Set it as the ped task
		pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_PRIMARY);
	}

	// Mark as enter a vehicle
	m_pVehicleEnterExit->bEntering = true;
	m_pVehicleEnterExit->pVehicle = pVehicle;
	m_pVehicleEnterExit->byteSeat = byteSeat;
}

void CPlayerEntity::ExitVehicle(eExitVehicleType exitType)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Are we not in a vehicle?
	if(!m_pVehicle)
	{
		// Are we entering a vehicle?
		if(HasVehicleEnterExit())
		{
			// Clear the vehicle entry task
			ClearVehicleEntryTask();
		}
		return;
	}

	CVector3 vecMoveSpeed;
	int iModelId;
	int iExitMode = 0xF;

	m_pVehicle->GetMoveSpeed(vecMoveSpeed);
	iModelId = EFLC::CModelManager::ModelHashToVehicleId(m_pVehicle->GetModelInfo()->GetHash());

	if(exitType == EXIT_VEHICLE_NORMAL)
	{
		if(vecMoveSpeed.fX < -10 || vecMoveSpeed.fX > 10 || vecMoveSpeed.fY < -10 || vecMoveSpeed.fY > 10)
		{
			switch(iModelId)
			{
			case 2: case 4: case 5: case 7: case 8: case 10: case 11:
			case 31: case 32: case 49: case 50: case 51: case 52:
			case 53: case 55: case 56: case 60: case 66: case 73:
			case 85: case 86: case 94: case 104:
				iExitMode = 0x40B;
				break;

			default:
				{
					if(iModelId != 12 && iModelId < 166)
						iExitMode = 0x100E;
				}
			}
		}
	}
	else
	{
		iExitMode = 0x9C4;
	}

	// Create the vehile exit task
	EFLC::CTaskComplexNewExitVehicle * pTask = new EFLC::CTaskComplexNewExitVehicle(m_pVehicle->GetGameVehicle(), iExitMode, 0, 0);

	// Did the task get created
	if(pTask)
	{
		// Set the ped task
		pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_PRIMARY);
	}

	// Mark as exiting vehicle
	m_pVehicleEnterExit->bExiting = true;
}

bool CPlayerEntity::GetClosestVehicle(bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat)
{
	// Are we spawned?
	if(IsSpawned())
	{
		float fCurrent = 6.0f;
		CVector3 vecVehiclePosition;
		CVehicleEntity * pClosestVehicle = nullptr;

		// Get our current position
		CVector3 vecPosition;
		GetPosition(vecPosition);

		// Loop through all current vehicles
		for(int i = 0; i < g_pCore->GetGame()->GetVehicleManager()->GetMax(); i++)
		{
			// Get a pointer to this vehicle
			CVehicleEntity * pThisVehicle = g_pCore->GetGame()->GetVehicleManager()->GetAt(i);

			if (!pThisVehicle)
				continue;

			// Get this vehicle position
			pThisVehicle->GetPosition(vecVehiclePosition);

			// Get the disance between us and the vehicle
			float fDistance = Math::GetDistanceBetweenPoints3D(vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecVehiclePosition.fX, vecVehiclePosition.fY, vecVehiclePosition.fZ);

			// Is the distance less than the current?
			if(fDistance < fCurrent)
			{
				// Set the current distance
				fCurrent = fDistance;

				// Set the closest vehicle pointer
				pClosestVehicle = pThisVehicle;
			}
		}

		// Do we have a valid vehicle pointer?
		if(!pClosestVehicle)
			return false;

		// Are we looking for a passenger seat?
		if(bPassenger)
		{
			// Loop through all passenger seats
			BYTE byteCurrentSeat = 0;

			for(BYTE i = 0; i < pClosestVehicle->GetMaxPassengers(); i++)
			{
				byteCurrentSeat = (i + 1);
			}

			// Do we not have a valid seat?
			if(byteCurrentSeat == 0)
				return false;

			// Set the seat
			byteSeat = byteCurrentSeat;
		}
		else
		{
			// Set the seat
			byteSeat = 0;
		}
		// Set the vehicle pointer
		*pVehicle = pClosestVehicle;
		return true;
	}

	return false;
}

void CPlayerEntity::GiveMoney(int iAmount)
{
	if(IsSpawned())
	{
		// this shows +/-$12345
		EFLC::CScript::AddScore(m_bytePlayerNumber, iAmount);

		// would take forever
		if(iAmount < -1000000 || iAmount > 1000000)
			m_pPlayerInfo->SetDisplayScore(m_pPlayerInfo->GetScore());
	}
}
void CPlayerEntity::SetMoney(int iAmount)
{
	if(IsSpawned())
	{
		m_pPlayerInfo->SetScore(iAmount);

		// would take forever
		int iDiff = (iAmount - m_pPlayerInfo->GetDisplayScore());

		if(iDiff < -1000000 || iDiff > 1000000)
			m_pPlayerInfo->SetDisplayScore(iAmount);
	}
}

void CPlayerEntity::ResetMoney()
{
	if(IsSpawned())
	{
		m_pPlayerInfo->SetScore(0);
		m_pPlayerInfo->SetDisplayScore(0);
	}
}

int CPlayerEntity::GetMoney()
{
	if(IsSpawned())
		return m_pPlayerInfo->GetScore();

	return 0;
}

void CPlayerEntity::ClearVehicleEntryTask()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting in a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_GET_IN_VEHICLE)
			{
				m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			}
		}
	}
}

void CPlayerEntity::ClearVehicleExitTask()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting out of a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_EXIT_VEHICLE)
			{
				m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			}
		}
	}
}

void CPlayerEntity::ResetVehicleEnterExit()
{
	// If player was exiting vehicle, process to proper reset first
	if(m_pVehicle && m_pVehicleEnterExit->bExiting)
	{
		// Reset the seat
		m_pVehicle->SetOccupant(m_byteSeat, nullptr);
		m_byteSeat = 0;

		// Reset the vehicle
		m_pVehicle = nullptr;
	}

	// Reset
	m_pVehicleEnterExit->bEntering = false;
	m_pVehicleEnterExit->pVehicle = nullptr;
	m_pVehicleEnterExit->byteSeat = 0;
	m_pVehicleEnterExit->bExiting = false;
	m_pVehicleEnterExit->bRequesting = false;

	// Clear the vehicle entry task
	ClearVehicleEntryTask();

	// Clear the vehicle exit task
	ClearVehicleExitTask();
}

void CPlayerEntity::ProcessVehicleEnterExit()
{
	if (IsSpawned())
	{
		if (InternalIsInVehicle())
		{
			if (m_pVehicleEnterExit->bEntering)
			{
				if (!IsGettingIntoAVehicle())
				{
					m_pVehicle = m_pVehicleEnterExit->pVehicle;
					m_byteSeat = m_pVehicleEnterExit->byteSeat;
					m_pVehicle->SetOccupant(m_byteSeat, this);
					ResetVehicleEnterExit();
				}
			}
		}
		else
		{
			if (m_pVehicleEnterExit->bExiting)
			{
				if (!IsGettingOutOfAVehicle())
				{
					ResetVehicleEnterExit();
				}
			}
		}
	}
}

bool CPlayerEntity::IsGettingIntoAVehicle()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is this task getting in a vehicle?
		if (pTask && pTask->GetType() == TASK_COMPLEX_NEW_GET_IN_VEHICLE)
			return true;
	}

	return false;
}

bool CPlayerEntity::IsJumping()
{
	if (IsSpawned())
	{
		// Get the ped task
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		if (pTask&& (pTask->GetType() == TASK_COMPLEX_JUMP || pTask->GetType() == TASK_SIMPLE_MOVE_IN_AIR))
			return true;
	}

	return false;
}
bool CPlayerEntity::IsGettingOutOfAVehicle()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);
		if (pTask && pTask->GetType() == TASK_COMPLEX_NEW_EXIT_VEHICLE)
				return true;
	}

	return false;
}


#define PED_INTERPOLATION_WARP_THRESHOLD 5
#define PED_INTERPOLATION_WARP_THRESHOLD_FOR_SPEED 5
#define TICK_RATE 50

void CPlayerEntity::UpdateTargetPosition()
{
	if(HasTargetPosition())
	{
		unsigned long ulCurrentTime = SharedUtility::GetTime();

		// Get our position
		CVector3 vecCurrentPosition;
		GetPosition(vecCurrentPosition);

		// Get the factor of time spent from the interpolation start
		// to the current time.
		float fAlpha = Math::Unlerp(m_interp.pos.ulStartTime, ulCurrentTime, m_interp.pos.ulFinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_interp.pos.fLastAlpha);
		m_interp.pos.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.pos.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if(fAlpha == 1.0f)
			m_interp.pos.ulFinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

		// Check if the distance to interpolate is too far
		if (!((vecCurrentPosition - m_interp.pos.vecTarget).Length() <= 3.0 /* maybe adjust this value a bit if we need earlier correction */))
		{
			// Abort all interpolation
			m_interp.pos.ulFinishTime = 0;
			vecNewPosition = m_interp.pos.vecTarget;
		}

		// Set our new position
		SetPosition(vecNewPosition, false);
	}
}

void CPlayerEntity::Interpolate()
{
		UpdateTargetPosition();
}

void CPlayerEntity::SetTargetPosition(const CVector3 &vecPosition, unsigned long ulDelay)
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Update our target position
		UpdateTargetPosition();

		// Get our position
		CVector3 vecCurrentPosition;
		GetPosition(vecCurrentPosition);

		// Set the target position
		m_interp.pos.vecTarget = vecPosition;

		// Calculate the relative error
		m_interp.pos.vecError = (vecPosition - vecCurrentPosition);

		// Get the interpolation interval
		unsigned long ulTime = SharedUtility::GetTime();
		m_interp.pos.ulStartTime = ulTime;
		m_interp.pos.ulFinishTime = (ulTime + ulDelay);

		// Initialize the interpolation
		m_interp.pos.fLastAlpha = 0.0f;
	}
}

void CPlayerEntity::RemoveTargetPosition()
{
	m_interp.pos.ulFinishTime = 0;
}

void CPlayerEntity::ResetInterpolation()
{
	RemoveTargetPosition();
}

void CPlayerEntity::Kill(bool bInstantly)
{
	// Are we spawned and not already dead?
	if(IsSpawned() && !IsDead())
	{
		// Are we getting killed instantly?
		if(bInstantly) 
		{

			// Create the dead task
			EFLC::CTaskSimpleDead * pTask = new EFLC::CTaskSimpleDead(CGameFunction::GetTimeOfDay(), 1, 0);

			// Did the task create successfully?
			if(pTask)
				pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}
		else 
		{ // We are not getting killed instantly

			// Are we already dying?
			if(IsDying())
				return;

			// Create the death task
			EFLC::CTaskComplexDie * pTask = new EFLC::CTaskComplexDie(0, 0, 44, 190, 4.0f, 0.0f, 1);

			// Did the task create successfully?
			if(pTask)
				pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}

		// Reset ped health, armour etc. values
		SetHealth(0);

		// Reset the control state
		CControlState controlState;
		SetControlState(&controlState);

		// Reset vehicle entry/exit flags
		m_pVehicleEnterExit->bExiting = true;
		ResetVehicleEnterExit();

		// Reset interpolation
		ResetInterpolation();
	}
}

bool CPlayerEntity::IsDying()
{
	if(IsSpawned())
	{
		EFLC::CTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);

		if(pTask)
			if(pTask->GetType() == TASK_COMPLEX_DIE)
				return true;
	}

	return false;
}

bool CPlayerEntity::IsDead()
{
	if(IsSpawned())
		return IsDying();

	return false;
}

EFLC::IEntity * CPlayerEntity::GetLastDamageEntity()
{
	if(IsSpawned())
		return m_pPlayerPed->GetLastDamageEntity();

	return nullptr;
}

bool CPlayerEntity::GetKillInfo(EntityId & playerId, EntityId & vehicleId, EntityId & weaponId)
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Reset player id and vehicle id
		playerId = INVALID_ENTITY_ID;
		vehicleId = INVALID_ENTITY_ID;
		weaponId = INVALID_ENTITY_ID;

		// Loop through all players
		for (EntityId i = 0; i < g_pCore->GetGame()->GetPlayerManager()->GetMax(); i++)
		{
			// Is this player connected and spawned?
			CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(i);

			if(pPlayer && pPlayer->IsSpawned())
			{
				// Is this player the last damage entity?
				if (GetLastDamageEntity() == (EFLC::IEntity *)pPlayer->GetPlayerPed()->GetPed())
				{
					// This player killed us
					playerId = i;
					weaponId = pPlayer->GetPlayerWeapons()->GetCurrentWeapon();
					break;
				}
				else
				{
					// Is this players vehicle the last damage entity?
					if(pPlayer->IsInVehicle() && !pPlayer->IsPassenger() && 
					   (GetLastDamageEntity() == pPlayer->GetVehicle()->GetGameVehicle()->GetVehicle()))
					{
						// This player killed us with their vehicle
						playerId = i;
						vehicleId = i;
						break;
					}
				}
			}
		}

		// Have we not yet found a killer?
		if(playerId == INVALID_ENTITY_ID && vehicleId == INVALID_ENTITY_ID)
		{
			// Loop through all players
			for(EntityId i = 0; i < g_pCore->GetGame()->GetVehicleManager()->GetMax(); i++)
			{
				// Is this player connected and spawned?
				CVehicleEntity * pVehicle = g_pCore->GetGame()->GetVehicleManager()->GetAt(i);

				if(pVehicle && pVehicle->IsSpawned())
				{
					// Is this vehicle the last damage entity?
					if(GetLastDamageEntity() == pVehicle->GetGameVehicle()->GetEntity())
					{
						// This vehicle killed us
						vehicleId = pVehicle->GetId();
						break;
					}
				}
			}
		}

		return true;
	}

	return false;
}

void CPlayerEntity::SetWeaponAimAtTask(const CVector3 &vecAimAt)
{
	if(IsSpawned())
	{
		EFLC::CTaskSimpleAimGun * pTask = new EFLC::CTaskSimpleAimGun(vecAimAt.fX, vecAimAt.fY, vecAimAt.fZ, 10000, 4, -4);

		// Was the task created?
		if(pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

void CPlayerEntity::SetWeaponShotAtTask(const CVector3 &vecAimAt)
{
	if (IsSpawned())
	{
		EFLC::CTaskSimpleFireGun * pTask = new EFLC::CTaskSimpleFireGun(vecAimAt.fX, vecAimAt.fY, vecAimAt.fZ, 10000, 4, -4);

		// Was the task created?
		if (pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

void CPlayerEntity::SetClothes(unsigned short ucBodyLocation, unsigned  char ucClothes)
{
	// Check if the bodylocation is out of our index
	if(ucBodyLocation > 10)
		return;

	if(IsSpawned()) {
		unsigned char ucClothesIdx = 0;
		unsigned uiDrawableVariations = m_pPlayerPed->GetNumberOfCharDrawableVariations(ucBodyLocation);

		for(unsigned uiDrawable = 0; uiDrawable < uiDrawableVariations; ++uiDrawable) 
		{
			unsigned uiTextureVariations = m_pPlayerPed->GetNumberOfCharTextureVariations(ucBodyLocation, uiDrawable);

			for(unsigned uiTexture = 0; uiTexture < uiTextureVariations; ++uiTexture) 
			{

				if(ucClothesIdx == ucClothes) 
				{
					m_pPlayerPed->SetClothes(ucBodyLocation, uiDrawable, uiTexture);
					SetClothesValue(ucBodyLocation, ucClothes);
					return;
				}

				++ucClothesIdx;
			}
		}

		m_pPlayerPed->SetClothes(ucBodyLocation, 0, 0);
		SetClothesValue(ucBodyLocation, 0);
	}
	else
		SetClothesValue(ucBodyLocation, ucClothes);
}

unsigned char CPlayerEntity::GetClothes(unsigned short ucBodyLocation)
{
	// Check if the bodylocation is out of our index
	if(ucBodyLocation > 10)
		return 0;

	return GetClothesValueFromSlot(ucBodyLocation);
}

void CPlayerEntity::Serialize(RakNet::BitStream * pBitStream)
{
	if (!IsInVehicle())
	{
		CNetworkPlayerSyncPacket PlayerPacket;

		// Apply current 3D Position to the sync package
		GetPlayerPed()->GetMatrix(PlayerPacket.matrix);
		GetMoveSpeed(PlayerPacket.vecMoveSpeed);
		GetTurnSpeed(PlayerPacket.vecTurnSpeed);

		PlayerPacket.bDuckState = m_pPlayerPed->IsDucking();
		PlayerPacket.fHeading = GetHeading();
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(PlayerPacket.pControlState);

		PlayerPacket.fHealth = GetHealth();
		PlayerPacket.fArmor = GetArmour();

		PlayerPacket.weapon.iAmmo = m_pPlayerWeapons->GetAmmo(m_pPlayerWeapons->GetCurrentWeapon());
		PlayerPacket.weapon.weaponType = m_pPlayerWeapons->GetCurrentWeapon();

		// Write player onfoot flag into raknet bitstream
		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);
		pBitStream->Write(PlayerPacket);

		// I know its hacky i will clean it up later its just working
		if (PlayerPacket.pControlState.IsAiming() || PlayerPacket.pControlState.IsFiring())
		{
			CNetworkPlayerWeaponSyncPacket WeaponPacket;

			if (PlayerPacket.pControlState.IsFiring())
			{
				m_pContextData->GetWeaponShotTarget(WeaponPacket.vecAimShotAtCoordinates);
				
			}
			else
			{
				m_pContextData->GetWeaponAimTarget(WeaponPacket.vecAimShotAtCoordinates);
			}

			m_pContextData->GetWeaponShotSource(WeaponPacket.vecShotSource);

			WeaponPacket.weapon.iAmmo = m_pPlayerWeapons->GetAmmo(m_pPlayerWeapons->GetCurrentWeapon());
			WeaponPacket.weapon.weaponType = m_pPlayerWeapons->GetCurrentWeapon();

			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_WEAPON);
			pBitStream->Write(WeaponPacket);
		}
	}
	else if (IsInVehicle() && !IsPassenger())
	{
		CNetworkPlayerVehicleSyncPacket VehiclePacket;
		VehiclePacket.vehicleId = m_pVehicle->GetId();

		m_pVehicle->GetQuaternion(VehiclePacket.matrix.quat);
		m_pVehicle->GetPosition(VehiclePacket.matrix.vecPosition);

		m_pVehicle->GetMoveSpeed(VehiclePacket.vecMoveSpeed);
		m_pVehicle->GetTurnSpeed(VehiclePacket.vecTurnSpeed);
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(VehiclePacket.ControlState);

		VehiclePacket.vehHealth = m_pVehicle->GetHealth();
		//VehiclePacket. = m_pVehicle->GetPetrolTankHealth();
		VehiclePacket.bEngineState = m_pVehicle->GetEngineState();
		VehiclePacket.playerArmor = GetArmour();
		VehiclePacket.playerHealth = GetHealth();
		VehiclePacket.weapon.iAmmo = m_pPlayerWeapons->GetAmmo(m_pPlayerWeapons->GetCurrentWeapon());
		VehiclePacket.weapon.weaponType = m_pPlayerWeapons->GetCurrentWeapon();

		EFLC::CScript::GetCarHeading(m_pVehicle->GetScriptingHandle(), &VehiclePacket.fHeading);

		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_VEHICLE);
		pBitStream->Write(VehiclePacket);
	}
	else if (IsInVehicle() && IsPassenger())
	{
		CNetworkPlayerPassengerSyncPacket PassengerPacket;

		g_pCore->GetGame()->GetPad()->GetCurrentControlState(PassengerPacket.ControlState);
		PassengerPacket.playerArmor = GetArmour();
		PassengerPacket.playerHealth = GetHealth();
		CLogFile::Printf("Armor: %f, Health: %f", GetArmour(), GetHealth());
		GetPosition(PassengerPacket.vecPosition);
		PassengerPacket.vehicleId = m_pVehicle->GetId();
		PassengerPacket.byteSeatId = m_byteSeat;
		
		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_PASSENGER);
		pBitStream->Write(PassengerPacket);
	}

	
}

void CPlayerEntity::Deserialize(RakNet::BitStream * pBitStream)
{
	// TODO: move sync to functions
	ePackageType eType;
	pBitStream->Read(eType);
	if (eType == RPC_PACKAGE_TYPE_PLAYER_ONFOOT)
	{
		CNetworkPlayerSyncPacket PlayerPacket;
		//Remove from vehicle if exit sync failed
		if (IsInVehicle() && !IsGettingOutOfAVehicle() && !HasVehicleEnterExit())
		{
			CLogFile::Print("Removing player from car, exit sync failed");
			RemoveFromVehicle();
			ResetVehicleEnterExit();
		}

		pBitStream->Read(PlayerPacket);

		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		if (m_pPlayerWeapons->GetCurrentWeapon() != PlayerPacket.weapon.weaponType)
		{
			m_pPlayerWeapons->GiveWeapon(PlayerPacket.weapon.weaponType, PlayerPacket.weapon.iAmmo); // Set our current weapon
			
		}
		if (m_pPlayerWeapons->GetAmmo(PlayerPacket.weapon.weaponType) != PlayerPacket.weapon.iAmmo) // Do we not have the right ammo?
			m_pPlayerWeapons->SetAmmo(PlayerPacket.weapon.weaponType, PlayerPacket.weapon.iAmmo); // Set our ammo

		m_pPlayerWeapons->SetCurrentWeapon(PlayerPacket.weapon.weaponType);

		if (!IsInVehicle() && !IsGettingIntoAVehicle() && !IsGettingOutOfAVehicle() && !HasVehicleEnterExit())
		{

			Matrix matrix;
#ifdef SYNC_TEST
			PlayerPacket.matrix.vecPosition.fX += 2.0f;
#endif
			SetHeading(PlayerPacket.fHeading);
			GetPlayerPed()->GetMatrix(matrix);
			matrix.vecForward = PlayerPacket.matrix.vecForward;
			matrix.vecRight = PlayerPacket.matrix.vecRight;
			matrix.vecUp = PlayerPacket.matrix.vecUp;
			m_pPlayerPed->RemoveFromWorld();
			GetPlayerPed()->SetMatrix(matrix);
			m_pPlayerPed->AddToWorld();
			//GetPlayerPed()->GetPed()->UpdatePhysicsMatrix(true);
			
			SetTargetPosition(PlayerPacket.matrix.vecPosition, interpolationTime);
			
			
			SetMoveSpeed(PlayerPacket.vecMoveSpeed);
			SetTurnSpeed(PlayerPacket.vecTurnSpeed);

			SetLastSyncPacket(PlayerPacket);
		}
		unsigned int uiPlayerIndex = GetScriptingHandle();


		GetPlayerPed()->SetDucking(PlayerPacket.bDuckState);

		SetHealth(PlayerPacket.fHealth);

		SetControlState(&PlayerPacket.pControlState);

		m_ulLastSyncReceived = SharedUtility::GetTime();
	}
	else if (eType == RPC_PACKAGE_TYPE_PLAYER_VEHICLE)
	{
		CNetworkPlayerVehicleSyncPacket VehiclePacket;
		pBitStream->Read(VehiclePacket);

#ifdef SYNC_TEST
		VehiclePacket.vehicleId += 1;
#endif

		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		if (IsInVehicle() && !HasVehicleEnterExit())
		{
			if (m_pVehicle->GetId() == VehiclePacket.vehicleId)
			{
				Matrix matrix;

				EFLC::CScript::SetCarHeading(m_pVehicle->GetScriptingHandle(), VehiclePacket.fHeading);
#ifdef SYNC_TEST
				VehiclePacket.matrix.vecPosition.fX += 5.0f;
#endif
				SetControlState(&VehiclePacket.ControlState);

				//m_pVehicle->GetGameVehicle()->GetMatrix(matrix);
				//matrix.vecForward = VehiclePacket.matrix.vecForward;
				//matrix.vecRight = VehiclePacket.matrix.vecRight;
				//matrix.vecUp = VehiclePacket.matrix.vecUp;
				//m_pVehicle->RemoveFromWorld();
				//m_pVehicle->GetGameVehicle()->SetMatrix(matrix);
				//m_pVehicle->AddToWorld();
				//m_pVehicle->GetGameVehicle()->GetVehicle()->UpdatePhysicsMatrix(true);


				m_pVehicle->SetTargetPosition(VehiclePacket.matrix.vecPosition, interpolationTime);
				m_pVehicle->SetQuaternion(VehiclePacket.matrix.quat);			
				
				m_pVehicle->SetMoveSpeed(VehiclePacket.vecMoveSpeed);
				m_pVehicle->SetTurnSpeed(VehiclePacket.vecTurnSpeed);
				m_pVehicle->SetHealth(VehiclePacket.vehHealth);
				//m_pVehicle->SetPetrolTankHealth(VehiclePacket.petrol);
				m_pVehicle->SetEngineState(VehiclePacket.bEngineState);

				SetArmour(VehiclePacket.playerArmor);
				SetHealth(VehiclePacket.playerHealth);

				m_pVehicle->SetLastSyncPacket(VehiclePacket);
			}
			else
			{
				g_pCore->GetGraphics()->GetChat()->Print("mhm player is not in the correct vehicle");
			}
		}
		else
		{
			if (!HasVehicleEnterExit())
			{
				ResetVehicleEnterExit();

				// Put the player in the vehicle if vehicle enter/exit sync failed or not completed
				if (g_pCore->GetGame()->GetVehicleManager()->GetAt(VehiclePacket.vehicleId))
				{
					PutInVehicle(g_pCore->GetGame()->GetVehicleManager()->GetAt(VehiclePacket.vehicleId), 0);
				}
			}
		}

		if (m_pPlayerWeapons->GetCurrentWeapon() != VehiclePacket.weapon.weaponType)
		{
			m_pPlayerWeapons->GiveWeapon((EFLC::eWeaponType)VehiclePacket.weapon.weaponType, VehiclePacket.weapon.iAmmo); // Set our current weapon
			m_pPlayerWeapons->SetCurrentWeapon((EFLC::eWeaponType)VehiclePacket.weapon.weaponType);
		}

		if (m_pPlayerWeapons->GetAmmo(VehiclePacket.weapon.iAmmo) != VehiclePacket.weapon.iAmmo) // Do we not have the right ammo?
			m_pPlayerWeapons->SetAmmo(VehiclePacket.weapon.weaponType, VehiclePacket.weapon.iAmmo); // Set our ammo


		m_ulLastSyncReceived = SharedUtility::GetTime();
	}
	else if (eType == RPC_PACKAGE_TYPE_PLAYER_PASSENGER)
	{
		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		CNetworkPlayerPassengerSyncPacket PassengerPacket;
		pBitStream->Read(PassengerPacket);

#ifdef SYNC_TEST
		PassengerPacket.vehicleId += 1;
#endif

		SetPosition(PassengerPacket.vecPosition);
		SetControlState(&PassengerPacket.ControlState);
		SetArmour(PassengerPacket.playerArmor);
		SetHealth(PassengerPacket.playerHealth);

		RemoveTargetPosition();

		if (!IsInVehicle() && !HasVehicleEnterExit())
		{
			ResetVehicleEnterExit();

			// Put the player in the vehicle if vehicle enter/exit sync failed or not completed
			if (g_pCore->GetGame()->GetVehicleManager()->GetAt(PassengerPacket.vehicleId))
			{
				PutInVehicle(g_pCore->GetGame()->GetVehicleManager()->GetAt(PassengerPacket.vehicleId), PassengerPacket.byteSeatId);
			}
		}
		
		m_ulLastSyncReceived = SharedUtility::GetTime();
	}


	// Check if we have additional packets
	if (pBitStream->Read(eType))
	{
		if (eType == RPC_PACKAGE_TYPE_PLAYER_WEAPON)
		{
			CNetworkPlayerWeaponSyncPacket AimSync;
			pBitStream->Read(AimSync);
			// First check if we're having any weapon data
			if (IsLocalPlayer())
				return;

			if (m_pPlayerWeapons->GetCurrentWeapon() != AimSync.weapon.weaponType) {
				// Set our current weapon
				m_pPlayerWeapons->GiveWeapon(AimSync.weapon.weaponType, AimSync.weapon.iAmmo);
			}
			// Do we not have the right ammo?
			if (m_pPlayerWeapons->GetAmmo(AimSync.weapon.iAmmo) != AimSync.weapon.iAmmo) {
				// Set our ammo
				m_pPlayerWeapons->SetAmmo(AimSync.weapon.weaponType, AimSync.weapon.iAmmo);
			}

			if (m_ControlState.IsAiming() && !m_ControlState.IsFiring())
			{
				m_pContextData->SetWeaponAimTarget(AimSync.vecAimShotAtCoordinates);

				unsigned int st = 0;
				EFLC::CScript::OpenSequenceTask(&st);
				EFLC::CScript::TaskAimGunAtCoord(GetScriptingHandle(), AimSync.vecAimShotAtCoordinates.fX, AimSync.vecAimShotAtCoordinates.fY, AimSync.vecAimShotAtCoordinates.fZ, 2000);
				EFLC::CScript::CloseSequenceTask(st);
				if (!EFLC::CScript::IsCharInjured(GetScriptingHandle()))
					EFLC::CScript::TaskPerformSequence(GetScriptingHandle(), st);
				EFLC::CScript::ClearSequenceTask(st);
			}
			else if (m_ControlState.IsFiring())
			{
				m_pContextData->SetWeaponShotSource(AimSync.vecShotSource);
				m_pContextData->SetWeaponShotTarget(AimSync.vecAimShotAtCoordinates);

				unsigned int st = 0;
				EFLC::CScript::OpenSequenceTask(&st);
				EFLC::CScript::TaskShootAtCoord(0, AimSync.vecAimShotAtCoordinates.fX, AimSync.vecAimShotAtCoordinates.fY, AimSync.vecAimShotAtCoordinates.fZ, 2000, 5); // 3 - fake shot
				EFLC::CScript::CloseSequenceTask(st);
				if (!EFLC::CScript::IsCharInjured(GetScriptingHandle()))
					EFLC::CScript::TaskPerformSequence(GetScriptingHandle(), st);
				EFLC::CScript::ClearSequenceTask(st);
			}
			else
			{
				unsigned int uiPlayerIndex = GetScriptingHandle();

				// Destroy shotat task
				_asm  push 36;
				_asm  push 0;
				_asm  push uiPlayerIndex;
				_asm  call COffsets::IV_Func__DeletePedTaskID;
				_asm  add esp, 0Ch;

				// Destroy aimat task
				_asm  push 35;
				_asm  push 0;
				_asm  push uiPlayerIndex;
				_asm  call COffsets::IV_Func__DeletePedTaskID;
				_asm  add esp, 0Ch;

			}
		}
	}
}

bool CPlayerEntity::IsOnScreen()
{
	CVector3 vecPos;
	GetPosition(vecPos);
	return g_pCore->GetGame()->GetCamera()->IsOnScreen(vecPos);
}


// !!! TEST CODE !!! I will clean this up later!

#include "Core/Game/EFLC/TaskInfo/CTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CTaskInfoWithCloneTask.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleAimPlayerProjectileInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleCarDriveTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleClimbTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleMeleeActionResultTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMBalanceTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMBraceTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMExplosionTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMFlinchTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMHighFallTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMJumpRollTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMOnFireTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleNMShotTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleSidewaysDiveTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSimpleThrowProjectileInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexClearVehicleSeatTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexClimbIntoVehicleTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexClimbLadderTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexCombatRetreatInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexFallAndGetUpTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexGangDrivebyTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexGunTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexJumpTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexNewExitVehicleTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexNewGetInVehicleTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexNewUseCoverInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexOnFireInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexOpenVehicleDoorTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexPickUpAndCarryObjectTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CComplexSlideIntoCoverInfo.h"
#include "Core/Game/EFLC/TaskInfo/CDeadInfo.h"
#include "Core/Game/EFLC/TaskInfo/CDieInfo.h"
#include "Core/Game/EFLC/TaskInfo/CPlayRandomAmbientsInfo.h"
#include "Core/Game/EFLC/TaskInfo/CScenarioTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSitDownIdleThenStandTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CSitIdleTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CStandUpTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CStatusAndTargetTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CStatusTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CVehicleTaskInfo.h"
#include "Core/Game/EFLC/TaskInfo/CMeleeTaskInfo.h"
#include "Core/Game/EFLC/CPedMoveBlend.h"

EFLC::CTaskInfo* CreateCTaskInfoFromTaskInfo(EFLC::ITaskInfo * pTaskInfo)
{
	switch (pTaskInfo->GetType())
	{
		case 0:
		return new EFLC::CTaskInfo(pTaskInfo);
		case 5:
		return new EFLC::CMeleeTaskInfo((EFLC::IMeleeTaskInfo*)pTaskInfo);
		case 6:
		return new EFLC::CSimpleMeleeActionResultTaskInfo((EFLC::ISimpleMeleeActionResultTaskInfo*)pTaskInfo);
		case 11:
		return new EFLC::CComplexJumpTaskInfo((EFLC::IComplexJumpTaskInfo*)pTaskInfo);
		case 14:
		return new EFLC::CSimpleCarDriveTaskInfo((EFLC::ISimpleCarDriveTaskInfo*)pTaskInfo);
		case 17:
		return nullptr; //IVComplexGunTaskInfo * pComplexGunTaskInfo = (IVComplexGunTaskInfo*) pTaskInfo;
		case 25:
		return new EFLC::CSimpleClimbTaskInfo((EFLC::ISimpleClimbTaskInfo*)pTaskInfo);
		case 26:
		return nullptr; //IVComplexClimbLadderTaskInfo * pComplexClimbLadderTaskInfo = (IVComplexClimbLadderTaskInfo*) pTaskInfo;
		case 27:
		return new EFLC::CPlayRandomAmbientsInfo((EFLC::IPlayRandomAmbientsInfo*)pTaskInfo);
		default:
		return nullptr;
	}
}


EFLC::CTaskInfo* CreateTaskInfoById(int taskid)
{
	switch (taskid)
	{
		case 0:
		return new EFLC::CTaskInfo();
		case 5:
		return new EFLC::CMeleeTaskInfo();
		case 6:
		return new EFLC::CSimpleMeleeActionResultTaskInfo();
		case 11:
		return new EFLC::CComplexJumpTaskInfo();
		case 14:
		return new EFLC::CSimpleCarDriveTaskInfo();
		case 17:
		return nullptr; //IVComplexGunTaskInfo * pComplexGunTaskInfo = (IVComplexGunTaskInfo*) pTaskInfo;
		case 25:
		return new EFLC::CSimpleClimbTaskInfo();
		case 26:
		return nullptr; //IVComplexClimbLadderTaskInfo * pComplexClimbLadderTaskInfo = (IVComplexClimbLadderTaskInfo*) pTaskInfo;
		case 27:
		return new EFLC::CPlayRandomAmbientsInfo();
		default:
		return nullptr;
	}
}

#define deleteTaskInfo ((void(__thiscall *)(EFLC::ITaskInfo**))((g_pCore->GetBase() + 0xA1F780)))
#define applyTaskInfo ((void(__thiscall *)(EFLC::ITaskInfo **, EFLC::ITaskInfo*))((g_pCore->GetBase() + 0xA1D980)))
#define processTaskInfo ((void(__stdcall *)(DWORD, EFLC::IPed*))((g_pCore->GetBase() + 0x525CE0)))

void CPlayerEntity::SerializeTaskInfo(RakNet::BitStream * pBitStream)
{
	if (!m_pPlayerPed->GetPed()->m_pPedIntelligence)
		return;

	EFLC::ITaskInfo * pTaskInfo = m_pPlayerPed->GetPed()->m_pPedIntelligence->m_pTaskInfo;
	if (!pTaskInfo)
		return;
	do
	{
		pBitStream->Write(pTaskInfo->GetType());
		EFLC::CTaskInfo* pCTaskInfo = CreateCTaskInfoFromTaskInfo(pTaskInfo);
		if (pCTaskInfo != nullptr)
		{
			pCTaskInfo->Serialize(pBitStream);
			delete pCTaskInfo;
		}
	}
	while (pTaskInfo = pTaskInfo->subTaskInfo);
}

void CPlayerEntity::DeserializeTaskInfo(RakNet::BitStream* pBitStream)
{
	if (!m_pPlayerPed)
		return;

	deleteTaskInfo(&m_pPlayerPed->GetPed()->m_pPedIntelligence->m_pTaskInfo);

	int TaskId;
	EFLC::ITaskComplex * pPrevTask = nullptr;
	if (pBitStream->Read(TaskId))
	{
		do
		{
			EFLC::CTaskInfo* pCTaskInfo = CreateTaskInfoById(TaskId);
			if (pCTaskInfo != nullptr)
			{
				if (!pCTaskInfo->Deserialize(pBitStream))
				{
					// DeserializeTasks fail (Error code 3 (task info type %d)), TaskId
					delete pCTaskInfo;
					return;
				}

				EFLC::ITask * pTask = (EFLC::ITask*)pCTaskInfo->GetTaskInfo()->CreateNetCloneTask();

				if (pTask)
				{
					EFLC::ITaskComplex * pTaskComplex = (EFLC::ITaskComplex*)pPrevTask;
					if (pPrevTask && !pPrevTask->IsSimple())
						pPrevTask->SetSubTask(pTask);
					pPrevTask = pTaskComplex;
				}


				applyTaskInfo(&m_pPlayerPed->GetPed()->m_pPedIntelligence->m_pTaskInfo, pCTaskInfo->GetTaskInfo());
				delete pCTaskInfo;
			}
		}
		while (pBitStream->Read(TaskId));

		processTaskInfo(m_pPlayerPed->GetPed()->m_pNetworkObject + 2056, m_pPlayerPed->GetPed());

		DWORD net = m_pPlayerPed->GetPed()->m_pNetworkObject;
		DWORD dwCall = g_pCore->GetBase() + 0x519BA0;
		_asm push esi;
		_asm mov esi, net;
		_asm call dwCall;
		_asm pop esi;
		
	
	}
}



CString MakeTaskInfoDebugString(EFLC::ITaskInfo* pInfo)
{
	CString info;
	switch (pInfo->GetType())
	{
		case 11:
		{
				   EFLC::IComplexJumpTaskInfo * pTaskInfo = (EFLC::IComplexJumpTaskInfo*)pInfo;

				   info.Format("ComplexJump(bHasPedJumped: %d, bJumpOnSpot : %d, bForceInAir : %d)",
							   pTaskInfo->m_bHasPedJumped,
							   pTaskInfo->m_bJumpOnSpot,
							   pTaskInfo->m_bForceInAir);
				   break;
		}
		case 14:
		{
				   EFLC::ISimpleCarDriveTaskInfo * pTaskInfo = (EFLC::ISimpleCarDriveTaskInfo*)pInfo;
				   info.Format("SimpleCarDrive(dwStatus: %d, Door Closed : %d, Engine On : %d, Horn : %d, Siren On : %d, Air Horn : %d, Full Beam On : %d)",
							   pTaskInfo->m_dwStatus,
							   pTaskInfo->m_dwFlags & 1,
							   pTaskInfo->m_dwFlags & 2,
							   pTaskInfo->m_dwFlags & 4,
							   pTaskInfo->m_dwFlags & 8,
							   pTaskInfo->m_dwFlags & 0x10,
							   pTaskInfo->m_dwFlags & 0x20);
				   break;
		}
		case 17:
		{

				   EFLC::IComplexGunTaskInfo * pTaskInfo = (EFLC::IComplexGunTaskInfo*)pInfo;
				   info.Format("ComplexGun(dwStatus: %d, dwTarget: 0x%x, wTargetId: %d, vecTarget(%f, %f, %f), dwFlags: %d, bOverridingAnims: %d, bCoverLeftFlag: %d, bCoverOverFlag: %d, dwCoverHeight: %d)",
							   pTaskInfo->m_dwStatus,
							   pTaskInfo->m_pTarget,				// 1C-20
							   pTaskInfo->m_wTargetId,			// 20-22
							   pTaskInfo->m_vecTarget,			// 30-40
							   pTaskInfo->m_dwFlags,				// 40-44
							   pTaskInfo->m_bOverridingAnims,		// 44-45
							   pTaskInfo->m_bCoverLeftFlag,		// 45-46
							   pTaskInfo->m_bCoverOverFlag,		// 46-47
							   pTaskInfo->m_bUnk,					// 47-48
							   pTaskInfo->m_dwCoverHeight		// 48-
							   );
				   break;
		}
		case 25:
		{
				   EFLC::ISimpleClimbTaskInfo * pTaskInfo = (EFLC::ISimpleClimbTaskInfo*)pInfo;
				   info.Format("SimpleClimb(byteClimbType: %d, bShimmyingLeft: %d, bShimmyingRight: %d, bPullingUp: %d, vecGrapPosition(%f, %f, %f))",
							   pTaskInfo->m_bClimbType,
							   pTaskInfo->m_bShimmyingLeft,
							   pTaskInfo->m_bShimmyingRight,
							   pTaskInfo->m_bPullingUp,
							   pTaskInfo->m_vecGrabPosition.fX,
							   pTaskInfo->m_vecGrabPosition.fY,
							   pTaskInfo->m_vecGrabPosition.fZ);
				   break;
		}
		case 26:
		{
				   EFLC::IComplexClimbLadderTaskInfo * pTaskInfo = (EFLC::IComplexClimbLadderTaskInfo*)pInfo;
				   info.Format("ComplexClimbLadder(isClimbingUp: %s, isClimbingDown: %s, isSlidingDown: %s)",
							   pTaskInfo->isClimbingUp ? "true" : "false",
							   pTaskInfo->isClimbingDown ? "true" : "false",
							   pTaskInfo->isSlidingDown ? "true" : "false");
				   break;
		}
		case 27:
		{
				   EFLC::IPlayRandomAmbientsInfo * pTaskInfo = (EFLC::IPlayRandomAmbientsInfo*)pInfo;
				   info.Format("PlayRandomAmbients(state: %i)", pTaskInfo->state);
				   break;
		}
		default:
		info.Format("TODO: type %d", pInfo->GetType());
		break;
	}

	return info;
}

#include "Core\Game\EFLC\CTask.h"


CString MakeSubTaskString(CString strName, EFLC::CTask* pTask)
{
	CString str;
	if (pTask)
	{
		str += strName;
		str += pTask->GetName();
		str += "\n";
		if (!pTask->IsSimple() && ((EFLC::CTaskComplex*)pTask)->GetSubTask())
			str += MakeSubTaskString(strName + "    ", ((EFLC::CTaskComplex*)pTask)->GetSubTask());
	}

	return str;
}

CString MakeTaskString(CString strName, EFLC::CTask* pTask)
{
	CString str;
	if (pTask)
	{
		str += strName;
		str += pTask->GetName();
		str += "\n";
		if (!pTask->IsSimple() && ((EFLC::CTaskComplex*)pTask)->GetSubTask())
			str += MakeSubTaskString("    ", ((EFLC::CTaskComplex*)pTask)->GetSubTask());
	}

	return str;
}

CString GetPedTasks(EFLC::CPed* pPed)
{
	CString strTasks;

	/** Prioritry Tasks **/
	strTasks += "Priority Tasks: \n";

	strTasks += MakeTaskString("PhysicalResponse: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PHYSICAL_RESPONSE));
	strTasks += MakeTaskString("EventResponseTemp: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_TEMP));
	strTasks += MakeTaskString("EventResponseNonTemp: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP));
	strTasks += MakeTaskString("Primary: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY));
	strTasks += MakeTaskString("Default: ", pPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_DEFAULT));
	strTasks += "\n";

	/**************************************************************************************************/

	strTasks += "Secondary Tasks: \n";
	strTasks += MakeTaskString("Attack: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_ATTACK));
	strTasks += MakeTaskString("Duck: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_DUCK));
	strTasks += MakeTaskString("Say: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_SAY));
	strTasks += MakeTaskString("Facial Complex: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_FACIAL_COMPLEX));
	strTasks += MakeTaskString("Partial Anim: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_PARTIAL_ANIM));
	strTasks += MakeTaskString("IK: ", pPed->GetPedTaskManager()->GetTask(TASK_SECONDARY_IK));
	strTasks += "\n";

	/**************************************************************************************************/

	strTasks += "Movement Tasks: \n";
	strTasks += MakeTaskString("Movement 1: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN0));
	strTasks += MakeTaskString("Movement 2: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN1));
	strTasks += MakeTaskString("Movement 3: ", pPed->GetPedTaskManager()->GetTask(TASK_MOVEMENT_UNKNOWN2));

	return strTasks;
}


CString CPlayerEntity::GetDebugText()
{
	CString strDebug = "";

#ifdef TASKINFO_TEST
	{
		EFLC::IPed* pIPed = m_pPlayerPed->GetPed();

		EFLC::IPedMoveBlendOnFoot *pPedMoveBlendOnFoot = pIPed->m_pPedMoveBlendOnFoot; // (IPedMoveBlendOnFoot*)((char*)pIPed + 0xA90);
		if (!pPedMoveBlendOnFoot)
			return "";
		strDebug += (CString("m_pNetworkObject: %s [0x%x]", pIPed->m_pNetworkObject ? "Created" : "Not created", pIPed->m_pNetworkObject));
		strDebug += "\n";
		strDebug += (CString("MoveBlend(v(%f, %f), vDest(%f, %f), AnimGroup: %d", pPedMoveBlendOnFoot->fX, pPedMoveBlendOnFoot->fY, pPedMoveBlendOnFoot->destX, pPedMoveBlendOnFoot->destY, pPedMoveBlendOnFoot->m_dwAnimGroup));
		strDebug += "\n";
		strDebug += (CString("Flags(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)", pPedMoveBlendOnFoot->m_dwFlags & 1, pPedMoveBlendOnFoot->m_dwFlags & 2, pPedMoveBlendOnFoot->m_dwFlags & 4, pPedMoveBlendOnFoot->m_dwFlags & 8, pPedMoveBlendOnFoot->m_dwFlags & 0x10, pPedMoveBlendOnFoot->m_dwFlags & 0x20, pPedMoveBlendOnFoot->m_dwFlags & 0x40, pPedMoveBlendOnFoot->m_dwFlags & 0x80, pPedMoveBlendOnFoot->m_dwFlags & 0x100, pPedMoveBlendOnFoot->m_dwFlags & 0x200, pPedMoveBlendOnFoot->m_dwFlags & 0x400, pPedMoveBlendOnFoot->m_dwFlags & 0x800, pPedMoveBlendOnFoot->m_dwFlags & 0x1000, pPedMoveBlendOnFoot->m_dwFlags & 0x2000));
		strDebug += "\n";
		strDebug += (CString("MoveBlend(14:%d, 18:%f, 1C:%d, 20:%d)", pPedMoveBlendOnFoot->field_14, pPedMoveBlendOnFoot->field_18, pPedMoveBlendOnFoot->field_1C, pPedMoveBlendOnFoot->field_20));
		strDebug += "\n";
		strDebug += (CString("MoveBlend(pPed:0x%x, 28:%f, 2C:%f, 30:%d, 34:%d, 38:%d, 40:%d)", pPedMoveBlendOnFoot->m_pPed, pPedMoveBlendOnFoot->field_28, pPedMoveBlendOnFoot->field_2C, pPedMoveBlendOnFoot->field_30, pPedMoveBlendOnFoot->field_34, pPedMoveBlendOnFoot->field_38, pPedMoveBlendOnFoot->field_40));
		strDebug += "\n";
		strDebug += (CString("MoveBlend(44:%d,48:%f,4C:%d,50:%d)", pPedMoveBlendOnFoot->field_44, pPedMoveBlendOnFoot->field_48, pPedMoveBlendOnFoot->field_4C, pPedMoveBlendOnFoot->m_dwFlags));
		strDebug += "\n";
		if (pIPed->m_pPedIntelligence)
		{
			if (pIPed->m_pPedIntelligence->m_pTaskInfo)
			{
				strDebug += (CString("TaskInfo [%s]", EFLC::GetTaskName(pIPed->m_pPedIntelligence->m_pTaskInfo->m_dwTaskId)));
				strDebug += "\n";
				strDebug += (CString("%s", MakeTaskInfoDebugString(pIPed->m_pPedIntelligence->m_pTaskInfo).Get()));
				strDebug += "\n";
				EFLC::ITaskInfo * pTaskInfo = pIPed->m_pPedIntelligence->m_pTaskInfo->subTaskInfo;
				while (pTaskInfo)
				{
					strDebug += (CString("subTaskInfo [%s]", EFLC::GetTaskName(pTaskInfo->m_dwTaskId)));
					strDebug += "\n";
					strDebug += (CString("%s", MakeTaskInfoDebugString(pTaskInfo).Get()));
					strDebug += "\n";
					pTaskInfo = pTaskInfo->subTaskInfo;
				}
			}
		}
		
		strDebug += "\n";
		strDebug += "\n";
		strDebug += "\n";

		strDebug += GetPedTasks(m_pPlayerPed);
	}
#endif

	return strDebug;
}