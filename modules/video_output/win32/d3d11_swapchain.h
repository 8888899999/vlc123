/*****************************************************************************
 * d3d11_swapchain.h: Direct3D11 swapchain handled by the display module
 *****************************************************************************
 * Copyright (C) 2014-2019 VLC authors and VideoLAN
 *
 * Authors: Martell Malone <martellmalone@gmail.com>
 *          Steve Lhomme <robux4@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef VLC_D3D11_SWAPCHAIN_H
#define VLC_D3D11_SWAPCHAIN_H

#include <vlc_common.h>

#include "../../video_chroma/d3d11_fmt.h"
#include "d3d11_shaders.h"

struct d3d11_local_swapchain
{
    vlc_object_t           *obj;
    d3d11_handle_t         *hd3d;
    d3d11_device_t         d3d_dev;

    const d3d_format_t     *pixelFormat;
    const struct dxgi_color_space *colorspace;

#if !VLC_WINSTORE_APP
    HWND                   swapchainHwnd;
#endif /* !VLC_WINSTORE_APP */
    IDXGISwapChain1        *dxgiswapChain;   /* DXGI 1.2 swap chain */
    IDXGISwapChain4        *dxgiswapChain4;  /* DXGI 1.5 for HDR metadata */

    ID3D11RenderTargetView *swapchainTargetView[D3D11_MAX_RENDER_TARGET];

    bool                   logged_capabilities;
};

bool LocalSwapchainSetupDevice( void **opaque, const libvlc_video_direct3d_device_cfg_t *cfg, libvlc_video_direct3d_device_setup_t *out );
void LocalSwapchainCleanupDevice( void *opaque );
void LocalSwapchainSwap( void *opaque );
bool LocalSwapchainUpdateOutput( void *opaque, const libvlc_video_direct3d_cfg_t *cfg, libvlc_video_output_cfg_t *out );
bool LocalSwapchainStartEndRendering( void *opaque, bool enter, const libvlc_video_direct3d_hdr10_metadata_t *p_hdr10 );
bool LocalSwapchainSelectPlane( void *opaque, size_t plane );

#endif /* VLC_D3D11_SWAPCHAIN_H */
