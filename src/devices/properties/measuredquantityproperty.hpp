/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEVICES_PROPERTIES_MEASUREDQUANTITYPROPERTY_HPP
#define DEVICES_PROPERTIES_MEASUREDQUANTITYPROPERTY_HPP

#include <memory>
#include <vector>

#include <QObject>
#include <QString>
#include <QVariant>

#include "src/data/datautil.hpp"
#include "src/devices/properties/baseproperty.hpp"
#include "src/devices/configurable.hpp"

using std::shared_ptr;
using std::vector;

namespace sv {
namespace devices {
namespace properties {

class MeasuredQuantityProperty : public BaseProperty
{
	Q_OBJECT

public:
	MeasuredQuantityProperty(shared_ptr<devices::Configurable> configurable,
		devices::ConfigKey config_key);

public:
	QVariant value() const override;
	data::measured_quantity_t measured_quantity_value() const;
	vector<data::measured_quantity_t> list_values() const;
	QString to_string() const override;

private:
	bool list_config();

	vector<data::measured_quantity_t> measured_quantity_list_;

public Q_SLOTS:
	void change_value(const QVariant) override;
	void on_value_changed(Glib::VariantBase) override;

};

} // namespace properties
} // namespace devices
} // namespece sv

#endif // DEVICES_PROPERTIES_MEASUREDQUANTITYPROPERTY_HPP
