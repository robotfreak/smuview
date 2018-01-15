/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>

#include <QDebug>

#include <libsigrokcxx/libsigrokcxx.hpp>

#include "multiplychannel.hpp"
#include "src/channels/basechannel.hpp"
#include "src/channels/mathchannel.hpp"
#include "src/data/analogsignal.hpp"

namespace sv {
namespace channels {

MultiplyChannel::MultiplyChannel(
		shared_ptr<data::AnalogSignal> signal1,
		shared_ptr<data::AnalogSignal> signal2,
		QString channel_group_name, double channel_start_timestamp) :
	MathChannel(channel_group_name, channel_start_timestamp),
	signal1_(signal1),
	signal2_(signal2),
	next_signal1_pos_(0),
	next_signal2_pos_(0)
	//channel_type_(ChannelType::MathChannel),
	//name_("MatchChannel"),
	//internal_name_("MatchChannel")
{
	assert(signal1_);
	assert(signal2_);

	connect(signal1_.get(), SIGNAL(sample_added()),
		this, SLOT(on_sample_added()));
	connect(signal2_.get(), SIGNAL(sample_added()),
		this, SLOT(on_sample_added()));
}

void MultiplyChannel::on_sample_added()
{
	size_t signal1_sample_count = signal1_->get_sample_count();
	if (signal1_sample_count < next_signal1_pos_)
		return;
	size_t signal2_sample_count = signal2_->get_sample_count();
	if (signal2_sample_count < next_signal2_pos_)
		return;

	// MultiplyChannel
	while (signal1_sample_count > next_signal1_pos_ &&
			signal1_sample_count > next_signal1_pos_) {

		data::sample_t sample1 = signal1_->get_sample(next_signal1_pos_, false);
		data::sample_t sample2 = signal2_->get_sample(next_signal2_pos_, false);

		double value = sample1.second * sample2.second;
		double time1 = sample1.first;
		double time2 = sample2.first;

		if (time1 == time2)
			// TODO
			BaseChannel::push_sample(&value, time1, signal1_->sr_quantity(),
				signal1_->sr_quantity_flags(), signal1_->sr_unit());
		else
			// TODO
			BaseChannel::push_sample(&value, time1>time2 ? time2 : time1,
				signal1_->sr_quantity(),
				signal1_->sr_quantity_flags(), signal1_->sr_unit());

		++next_signal1_pos_;
		++next_signal2_pos_;
	}
}

} // namespace devices
} // namespace sv