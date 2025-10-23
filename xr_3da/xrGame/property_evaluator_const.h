////////////////////////////////////////////////////////////////////////////
//	Module 		: property_evaluator_const.h
//	Created 	: 12.03.2004
//  Modified 	: 26.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Property evaluator const
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "property_evaluator.h"

template <typename _object_type>
class CPropertyEvaluatorConst : public CPropertyEvaluator<_object_type> {
protected:
	typedef CPropertyEvaluator<_object_type>		inherited;
	using inherited::m_evaluator_name;

protected:
	typedef typename inherited::_value_type		_val_type;
	_val_type			m_value;

public:
	IC					CPropertyEvaluatorConst	(_val_type value, LPCSTR evaluator_name = "");
	virtual _val_type	evaluate				();
};


#include "property_evaluator_const_inline.h"