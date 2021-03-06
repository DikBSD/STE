/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IMAGEPROC_XSPLINE_H_
#define IMAGEPROC_XSPLINE_H_

#include "VirtualFunction.h"
#include <boost/dynamic_bitset.hpp>
#include <QPointF>
#include <QLineF>
#include <vector>

namespace imageproc
{

/**
 * \brief An open, uniform X-Spline.
 */
class XSpline
{
public:
	int numControlPoints() const;

	int numSegments() const;

	void appendControlPoint(QPointF const& pos, double weight);

	void insertControlPoint(int idx, QPointF const& pos, double weight);

	void eraseControlPoint(int idx);

	QPointF controlPointPosition(int idx) const { return m_controlPoints[idx].pos; }

	void moveControlPoint(int idx, QPointF const& pos);

	void setControlPointWeight(int idx, double weight);

	QPointF eval(double t) const;

	QPointF eval(int segment, double t) const;

	QPointF pointClosestTo(QPointF to, double* t, double accuracy = 0.2) const;

	QPointF pointClosestTo(QPointF to, double accuracy = 0.2) const;

	std::vector<QPointF> toPolyline(double accuracy = 0.2) const;

	void fit(std::vector<QPointF> const& samples, boost::dynamic_bitset<> const* fixed_points = 0);

	void swap(XSpline& other) { m_controlPoints.swap(other.m_controlPoints); }
private:
	struct ControlPoint
	{
		QPointF pos;
		double weight;

		ControlPoint() : weight() {}

		ControlPoint(QPointF const& p, double w) : pos(p), weight(w) {}
	};

	static QPointF evalImpl(std::vector<ControlPoint> const& pts, double t);

	void eval2Impl(double t, VirtualFunction2<void, int, double>& out) const;

	void eval2Impl(int segment, double t, VirtualFunction2<void, int, double>& out) const;

	void maybeInsertMorePoints(
		std::vector<QPointF>& polyline, double sq_accuracy,
		int segment, double prev_t, QPointF const& prev_pt,
		double next_t, QPointF const& next_pt) const;

	static double sqDistToLine(QPointF const& pt, QLineF const& line);

	std::vector<ControlPoint> m_controlPoints;
};


inline void swap(XSpline& o1, XSpline& o2)
{
	o1.swap(o2);
}

} // namespace imageproc

#endif
