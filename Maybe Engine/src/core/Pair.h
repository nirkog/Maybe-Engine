#pragma once

namespace mb {

	template<typename F, typename S>
	struct Pair
	{
		F first;
		S second;

		static Pair<F, S>& Create(F first, S second)
		{
			Pair<F, S> pair;
			pair.first = first;
			pair.second = second;

			return pair;
		}
	};

}