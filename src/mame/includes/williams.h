/*************************************************************************

    Driver for early Williams games

**************************************************************************/


#include "machine/6821pia.h"
#include "audio/williams.h"

class williams_state : public driver_device
{
public:
	williams_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_nvram(*this, "nvram"),
		m_videoram(*this, "videoram"),
		m_blaster_palette_0(*this, "blaster_pal0"),
		m_blaster_scanline_control(*this, "blaster_scan"),
		m_williams2_tileram(*this, "williams2_tile")
	{ }

	required_shared_ptr<UINT8>	m_nvram;
	UINT8 *m_mayday_protection;
	required_shared_ptr<UINT8> m_videoram;
	optional_shared_ptr<UINT8> m_blaster_palette_0;
	optional_shared_ptr<UINT8> m_blaster_scanline_control;
	optional_shared_ptr<UINT8> m_williams2_tileram;
	UINT8 m_blitter_config;
	UINT16 m_blitter_clip_address;
	UINT8 m_blitter_window_enable;
	UINT8 m_williams2_tilemap_config;
	UINT8 m_cocktail;
	UINT8 m_blaster_bank;
	UINT8 m_vram_bank;
	UINT16 m_joust2_current_sound_data;
	UINT8 m_port_select;
	rgb_t *m_palette_lookup;
	UINT8 m_blitterram[8];
	UINT8 m_blitter_xor;
	UINT8 m_blitter_remap_index;
	const UINT8 *m_blitter_remap;
	UINT8 *m_blitter_remap_lookup;
	rgb_t m_blaster_color0;
	UINT8 m_blaster_video_control;
	tilemap_t *m_bg_tilemap;
	UINT16 m_tilemap_xscroll;
	UINT8 m_williams2_fg_color;
	DECLARE_WRITE8_MEMBER(williams_vram_select_w);
	DECLARE_WRITE8_MEMBER(williams2_bank_select_w);
	DECLARE_WRITE8_MEMBER(williams_cmos_w);
	DECLARE_WRITE8_MEMBER(bubbles_cmos_w);
	DECLARE_WRITE8_MEMBER(williams_watchdog_reset_w);
	DECLARE_WRITE8_MEMBER(williams2_watchdog_reset_w);
	DECLARE_WRITE8_MEMBER(williams2_7segment_w);
	DECLARE_WRITE8_MEMBER(defender_video_control_w);
	DECLARE_WRITE8_MEMBER(defender_bank_select_w);
	DECLARE_READ8_MEMBER(mayday_protection_r);
	DECLARE_WRITE8_MEMBER(sinistar_vram_select_w);
	DECLARE_WRITE8_MEMBER(blaster_vram_select_w);
	DECLARE_WRITE8_MEMBER(blaster_bank_select_w);
	DECLARE_WRITE8_MEMBER(williams2_paletteram_w);
	DECLARE_WRITE8_MEMBER(williams2_fg_select_w);
	DECLARE_READ8_MEMBER(williams_video_counter_r);
	DECLARE_READ8_MEMBER(williams2_video_counter_r);
	DECLARE_WRITE8_MEMBER(williams2_bg_select_w);
	DECLARE_WRITE8_MEMBER(williams2_tileram_w);
	DECLARE_WRITE8_MEMBER(williams2_xscroll_low_w);
	DECLARE_WRITE8_MEMBER(williams2_xscroll_high_w);
	DECLARE_WRITE8_MEMBER(blaster_remap_select_w);
	DECLARE_WRITE8_MEMBER(blaster_video_control_w);
	DECLARE_WRITE8_MEMBER(williams_blitter_w);
	DECLARE_WRITE8_MEMBER(williams2_blit_window_enable_w);
	DECLARE_CUSTOM_INPUT_MEMBER(williams_mux_r);
	DECLARE_DRIVER_INIT(sinistar);
	DECLARE_DRIVER_INIT(blaster);
	DECLARE_DRIVER_INIT(stargate);
	DECLARE_DRIVER_INIT(playball);
	DECLARE_DRIVER_INIT(defender);
	DECLARE_DRIVER_INIT(mayday);
	DECLARE_DRIVER_INIT(mysticm);
	DECLARE_DRIVER_INIT(lottofun);
	DECLARE_DRIVER_INIT(alienaru);
	DECLARE_DRIVER_INIT(defndjeu);
	DECLARE_DRIVER_INIT(spdball);
	DECLARE_DRIVER_INIT(inferno);
	DECLARE_DRIVER_INIT(splat);
	DECLARE_DRIVER_INIT(joust);
	DECLARE_DRIVER_INIT(alienar);
	DECLARE_DRIVER_INIT(tshoot);
	DECLARE_DRIVER_INIT(robotron);
	DECLARE_DRIVER_INIT(bubbles);
	TILE_GET_INFO_MEMBER(get_tile_info);
	DECLARE_MACHINE_START(defender);
	DECLARE_MACHINE_RESET(defender);
	DECLARE_VIDEO_START(williams);
	DECLARE_MACHINE_START(williams2);
	DECLARE_MACHINE_RESET(williams2);
	DECLARE_VIDEO_START(williams2);
	DECLARE_MACHINE_START(williams);
	DECLARE_MACHINE_RESET(williams);
	DECLARE_MACHINE_START(blaster);
	DECLARE_MACHINE_RESET(blaster);
	DECLARE_VIDEO_START(blaster);
	DECLARE_MACHINE_START(williams_common);
	DECLARE_MACHINE_RESET(williams_common);
	UINT32 screen_update_williams(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_williams2(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_blaster(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(williams_count240_off_callback);
	TIMER_CALLBACK_MEMBER(williams2_endscreen_off_callback);
	TIMER_CALLBACK_MEMBER(williams_deferred_snd_cmd_w);
	TIMER_CALLBACK_MEMBER(blaster_deferred_snd_cmd_w);
	TIMER_CALLBACK_MEMBER(williams2_deferred_snd_cmd_w);
	TIMER_DEVICE_CALLBACK_MEMBER(williams_va11_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(williams_count240_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(williams2_va11_callback);
	TIMER_DEVICE_CALLBACK_MEMBER(williams2_endscreen_callback);
};


class joust2_state : public williams_state
{
public:
	joust2_state(const machine_config &mconfig, device_type type, const char *tag)
		: williams_state(mconfig, type, tag),
		m_cvsd_sound(*this, "cvsd") { }

	required_device<williams_cvsd_sound_device> m_cvsd_sound;
	DECLARE_DRIVER_INIT(joust2);
	DECLARE_MACHINE_START(joust2);
	DECLARE_MACHINE_RESET(joust2);
	TIMER_CALLBACK_MEMBER(joust2_deferred_snd_cmd_w);
};

/*----------- defined in drivers/williams.c -----------*/

void defender_install_io_space(address_space &space);


/*----------- defined in machine/williams.c -----------*/

/* Generic old-Williams PIA interfaces */
extern const pia6821_interface williams_pia_0_intf;
extern const pia6821_interface williams_muxed_pia_0_intf;
extern const pia6821_interface williams_49way_pia_0_intf;
extern const pia6821_interface williams_49way_muxed_pia_0_intf;
extern const pia6821_interface williams_pia_1_intf;
extern const pia6821_interface williams_snd_pia_intf;
extern const pia6821_interface williams_snd_pia_b_intf;

/* Game-specific old-Williams PIA interfaces */
extern const pia6821_interface lottofun_pia_0_intf;
extern const pia6821_interface sinistar_snd_pia_intf;
extern const pia6821_interface playball_pia_1_intf;
extern const pia6821_interface blaster_pia_1_intf;
extern const pia6821_interface spdball_pia_3_intf;

/* Generic later-Williams PIA interfaces */
extern const pia6821_interface williams2_muxed_pia_0_intf;
extern const pia6821_interface williams2_pia_1_intf;
extern const pia6821_interface williams2_snd_pia_intf;

/* Game-specific later-Williams PIA interfaces */
extern const pia6821_interface mysticm_pia_0_intf;
extern const pia6821_interface mysticm_pia_1_intf;
extern const pia6821_interface tshoot_pia_0_intf;
extern const pia6821_interface tshoot_pia_1_intf;
extern const pia6821_interface tshoot_snd_pia_intf;
extern const pia6821_interface joust2_pia_1_intf;

/*----------- defined in video/williams.c -----------*/

#define WILLIAMS_BLITTER_NONE		0		/* no blitter */
#define WILLIAMS_BLITTER_SC01		1		/* SC-01 blitter */
#define WILLIAMS_BLITTER_SC02		2		/* SC-02 "fixed" blitter */

#define WILLIAMS_TILEMAP_MYSTICM	0		/* IC79 is a 74LS85 comparator */
#define WILLIAMS_TILEMAP_TSHOOT		1		/* IC79 is a 74LS157 selector jumpered to be enabled */
#define WILLIAMS_TILEMAP_JOUST2		2		/* IC79 is a 74LS157 selector jumpered to be disabled */

