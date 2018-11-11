/****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139]. 
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the 
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

/* Now building all code at once, so include vectors. MAC address is embedded
   in build for now */
SECTIONS
{
        
        /* start location 0x54 */
        .ro_mac_address (ALIGN((. - _enc_offset), 16) + _enc_offset):
        {
        _FlsMACAddress = ABSOLUTE(.);
        *(.ro_mac_address) /* Mac Address 8 bytes*/
        . = ALIGN (0x10);
        } > flash        
        
        .ro_ota_header (ALIGN((. - _enc_offset), 16) + _enc_offset):
        {
        _FlsOtaHeader = ABSOLUTE(.);
        *(.ro_ota_header) /* Ota Header 69 bytes*/
        . = ALIGN (0x10);
        } > flash   
        
        .ro_se_lnkKey (ALIGN((. - _enc_offset), 16) + _enc_offset):
	{
	_FlsLinkKey = ABSOLUTE(.);
	*(.ro_se_lnkKey)  /* Link Key 16 bytes*/
	. = ALIGN (0x10);
        } > flash

	
}
