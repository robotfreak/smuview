/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018 Frank Stettner <frank-stettner@gmx.net>
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

#include <memory>

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "welcometab.hpp"
#include "src/session.hpp"

using std::shared_ptr;

namespace sv {
namespace tabs {

WelcomeTab::WelcomeTab(Session &session, QMainWindow *parent) :
	BaseTab(session, parent)
{
	setup_ui();
}

void WelcomeTab::setup_ui()
{
	QVBoxLayout *layout = new QVBoxLayout();

	QString welcome("");
	welcome.
		append("<center>").
		append("<big><b>Welcome to SmuView!</b></big><br>").
		append("Multimeters, Power Supplies and Loads<br>").
		append("</center>");

	QLabel *welcome_label = new QLabel();
	welcome_label->setText(welcome);
	layout->addWidget(welcome_label);

	this->setLayout(layout);
}

} // namespace tabs
} // namespace sv
