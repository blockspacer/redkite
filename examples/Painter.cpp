/**
 * File name: Painter.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkMain.h"
#include "RkWidget.h"
#include "RkPainter.h"
#include "RkPoint.h"
#include "RkLog.h"
#include "RkEvent.h"

/**
 * This is an example how to draw on a widget by using RkPainter.
 */

class  PainterExample: public RkWidget {
  public:
        PainterExample(RkMain *app)
                : RkWidget(app)
                , clickPoint(50, 50)
                , startDraw{false}
        {
                // Set widget background color.
                setBackgroundColor(80, 80, 80);
        }

  protected:
        // paintEvent is re-implemented from RkWidget interface.
        // paintEvent is called every time the widget needs to be painted.
        void paintEvent(RkPaintEvent *event) final
        {
                RK_UNUSED(event);

                /**
                 * There are two options to draw. Draw directly to a widget or
                 * draw first on an image, and than draw the image on the widget.
                 * The second option is to avoid flickering.
                 */
                if (startDraw) {

                        // Create the image if the widget size changed or if the image was not created.
                        if (image.width() != width() || image.height() != height()) {
                                RkImage im(width(), height());
                                // Because there is no copy constructor developed yet for RkImage.
                                image = im;
                        }

                        // Use RkPainter to draw on the image.
                        RkPainter painter(&image);

                        // Fill the rect with the widget background color.
                        painter.fillRect(rect(), background());

                        // Create a pen with color, with and style.
                        RkPen pen(RkColor(255, 0, 0));
                        pen.setWidth(1);
                        pen.setStyle(RkPen::PenStyle::DashLine);

                        // Set RkPainter pen.
                        painter.setPen(pen);

                        // Draw some circles and lines.
                        painter.drawCircle(50, 50, 40);
                        painter.drawLine(50, 50, 100, 100);
                        painter.drawCircle(clickPoint.x() + 40 / 2, clickPoint.y() + 40/2, 40);
                        painter.drawLine(clickPoint, RkPoint(clickPoint.x() + 80, clickPoint.y() + 80));

                        // Change the pen style and draw.
                        pen.setStyle(RkPen::PenStyle::DotLine);
                        pen.setColor(RkColor(0, 255, 0));
                        painter.setPen(pen);
                        painter.drawCircle(clickPoint.x() + 40 / 2, clickPoint.y() - 40/2, 40);
                        painter.drawLine(clickPoint, RkPoint(clickPoint.x() + 80, clickPoint.y() - 80));

                        // Change the pen style and draw again.
                        pen.setStyle(RkPen::PenStyle::SolidLine);
                        pen.setColor(RkColor(0, 0, 255));
                        painter.setPen(pen);
                        painter.drawCircle(clickPoint.x() - 40 / 2, clickPoint.y() - 40/2, 40);
                        painter.drawLine(clickPoint, RkPoint(clickPoint.x() - 80, clickPoint.y() - 80));

                        // Draw text with a font color and style.
                        int y = 50;
                        painter.fillRect(RkRect(50, y, 100, 25), RkColor(255, 255, 255));
                        RkFont font = painter.font();
                        font.setStyle(RkFont::Style::Italic);
                        painter.setFont(font);
                        painter.drawText({50, y, 100, 25}, "Hello!");

                        y += 55;
                        painter.fillRect(RkRect(50, y, 100, 25), RkColor(255, 255, 255));
                        painter.drawText({50, y, 100, 25}, "Hello!", Rk::Alignment::AlignLeft);

                        y += 55;
                        painter.fillRect(RkRect(50, y, 100, 25), RkColor(255, 255, 255));
                        painter.drawText({50, y, 100, 25}, "Hello!", Rk::Alignment::AlignRight);
                        painter.drawRect(RkRect(50, y, 100, 25));

                        // Create the RkPainter that will draw on widget.
                        RK_LOG_INFO("-----------------> RkPainter");
                        RkPainter paint(this);
                        RK_LOG_INFO("-----------------> RkPainter1");
                        // Draw the image that was create before.
                        paint.drawImage(image, 0, 0);
                        RK_LOG_INFO("-----------------> RkPainter2");
                }
        }

        void mouseButtonPressEvent(RkMouseEvent* event) final
        {
                clickPoint = RkPoint(event->x(), event->y());
                startDraw = !startDraw;
                update();
        }

        void mouseMoveEvent(RkMouseEvent* event) final
        {
                if (startDraw) {
                        clickPoint = RkPoint(event->x(), event->y());
                        update();
                }
        }


  private:
        RkPoint clickPoint;
        bool startDraw;
        RkImage image;
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new PainterExample(&app);
    widget->setTitle("Painter Example");
    widget->setSize(350, 350);
    widget->show();

    return app.exec();
}
