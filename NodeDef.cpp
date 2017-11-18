#include "stdafx.h"
#include "NodeDef.h"
#include <map>

namespace ai
{


	int numOpArgs(OpDef op)
	{
		static const std::map<OpDef, int> op_args = {
			{ OpDef::plus, 2 },
			{ OpDef::minus, 2 },
			{ OpDef::multiply, 2 },
			{ OpDef::divide, 2 },
			{ OpDef::exponent, 1 },
			{ OpDef::polynomial, 1 },
			{ OpDef::none, 0 },
		};
		return op_args.find(op)->second;
	};


	NodeDef::NodeDef(NodeDef&&) noexcept = default;
	NodeDef& NodeDef::operator=(NodeDef&&) noexcept = default;
	NodeDef::~NodeDef() = default;
	NodeDef::NodeDef(const NodeDef&) = default;
	NodeDef& NodeDef::operator=(const NodeDef&) = default;
	NodeDef NodeDef::Clone()
	{
		return NodeDef(std::make_shared<impl>(*pimpl));
	}

	NodeDef::NodeDef(std::shared_ptr<impl> _pimpl) : pimpl(_pimpl) {};

	NodeDef::NodeDef(double _val)
		: pimpl(new impl(_val)) {}

	NodeDef::NodeDef(OpDef _op, const std::vector<NodeDef>& _children)
		: pimpl(new impl(_op, _children)) {}

	/* Getters and Setters */
	double NodeDef::GetValue() const { return pimpl->val; }

	void NodeDef::SetValue(double _val) { pimpl->val = _val; }

	OpDef NodeDef::GetOp() const { return pimpl->op; }

	void NodeDef::SetOp(OpDef _op) { pimpl->op = _op; }

	std::vector<NodeDef>& NodeDef::GetChildren() const { return pimpl->children; }

	std::vector<NodeDef> NodeDef::GetParents() const {
		std::vector<NodeDef> _parents;
		for (std::weak_ptr<impl> parent : pimpl->parents) {
			_parents.emplace_back(parent.lock());
		}
		return _parents;
	}



	bool NodeDef::operator==(const NodeDef& rhs) const
	{
		return pimpl.get() == rhs.pimpl.get();
	}

	NodeDef::impl::impl(double _val) :
		val(_val),
		op(OpDef::none) {}

	NodeDef::impl::impl(OpDef _op, const std::vector<NodeDef>& _children)
		: op(_op) {
		for (const NodeDef& v : _children) {
			children.emplace_back(v.pimpl);
		}
	}

}

namespace std
{
	size_t hash<ai::NodeDef>::operator()(const ai::NodeDef& v) const
	{
		return std::hash<std::shared_ptr<ai::NodeDef::impl> >{}(v.pimpl);
	}
}
