/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "opentx.h"

const uint8_t LBM_LAYOUT_1P2[] = {
#include "mask_layout1+2.lbm"
};

const ZoneOption OPTIONS_LAYOUT_1P2[] = {
  { STR_TOP_BAR, ZoneOption::Bool },
  { STR_FLIGHT_MODE, ZoneOption::Bool },
  { STR_SLIDERS, ZoneOption::Bool },
  { STR_TRIMS, ZoneOption::Bool },
  { NULL, ZoneOption::Bool }
};

const Zone ZONES_LAYOUT_1P2[3] = {

  { 48, 60, 384, 70 },
  { 48, 142, 186, 70},
  { 246, 142, 186, 70}
};

class Layout1P2: public Layout
{
  public:
    Layout1P2(const LayoutFactory * factory, Layout::PersistentData * persistentData):
      Layout(factory, persistentData)
    {
    }

    virtual void create()
    {
      Layout::create();
      persistentData->options[0].boolValue = true;
      persistentData->options[1].boolValue = true;
      persistentData->options[2].boolValue = true;
      persistentData->options[3].boolValue = true;
    }

    virtual unsigned int getZonesCount() const
    {
      return DIM(ZONES_LAYOUT_1P2);
    }

    virtual Zone getZone(unsigned int index) const
    {
      return ZONES_LAYOUT_1P2[index];
    }

    virtual void refresh();
};

void Layout1P2::refresh()
{
  theme->drawBackground();

  if (persistentData->options[0].boolValue) {
    drawTopBar();
  }

  if (persistentData->options[1].boolValue) {
    // Flight mode
    lcdDrawSizedText(LCD_W / 2 - getTextWidth(g_model.flightModeData[mixerCurrentFlightMode].name,
                                              sizeof(g_model.flightModeData[mixerCurrentFlightMode].name),
                                              ZCHAR | SMLSIZE) / 2,
                     232,
                     g_model.flightModeData[mixerCurrentFlightMode].name,
                     sizeof(g_model.flightModeData[mixerCurrentFlightMode].name), ZCHAR | SMLSIZE);
  }

  if (persistentData->options[2].boolValue) {
    // Pots and rear sliders positions
    drawMainPots();
  }

  if (persistentData->options[3].boolValue) {
    // Trims
    drawTrims(mixerCurrentFlightMode);
  }

  Layout::refresh();
}

BaseLayoutFactory<Layout1P2> layout1P2("Layout1P2", LBM_LAYOUT_1P2, OPTIONS_LAYOUT_1P2);

