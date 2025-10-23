#pragma once
#include "../states/monster_state_attack.h"

template<typename _Object>
class	CBloodsuckerStateAttack : public CStateMonsterAttack<_Object> {
	typedef CStateMonsterAttack<_Object> inherited_attack;
	using	inherited_attack::add_state;
	using	inherited_attack::current_substate;
	using	inherited_attack::select_state;
	using	inherited_attack::prev_substate;
	using	inherited_attack::get_state;
	using	inherited_attack::get_state_current;
	using	inherited_attack::object;
	using	inherited_attack::m_time_start_check_behinder;
	using	inherited_attack::check_steal_state;
	using	inherited_attack::check_run_attack_state;
	using	inherited_attack::check_find_enemy_state;
	using	inherited_attack::check_camp_state;
	using	inherited_attack::check_home_point;

	u32				m_time_stop_invis;
	Fvector			m_dir_point;

public:
					CBloodsuckerStateAttack		(_Object *obj);
	virtual			~CBloodsuckerStateAttack	();

	virtual	void	initialize					();
	virtual	void	execute						();
	virtual	void	finalize					();
	virtual	void	critical_finalize			();
	
	virtual void	setup_substates				();
private:
			void	update_invisibility			();
			bool	check_hiding				();
};

#include "bloodsucker_attack_state_inline.h"
