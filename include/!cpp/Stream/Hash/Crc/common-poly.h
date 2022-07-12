/*
	Copyright 2020 Bga <bga.email@gmail.com>

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once

#include <!cpp/common.h>

#pragma push_macro("Self")
#define Self Crc

namespace Bga { namespace Stream { namespace Hash { namespace Self { 
	

//# [https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Polynomial_representations_of_cyclic_redundancy_checks]

#if 0
	inFilePath = (ARGV[1] or "-")
	outFilePath = (ARGV[2] or "-")
	inFile = ((inFilePath == "-") ? STDIN : open(inFilePath, "rt"))
	outFile = (outFilePath == "-") ? STDOUT : open(outFilePath, "wt+")
	outFile.write((inFile
		.read()
		.gsub(/\|\-\n\n\|\s*?([^\n]+?)[ \t]*\n\|\s*?([^\n]+?)\n\|\s*(0x[0-9a-fA-F]+)[ \t]*\n/m,  "\\1  = \\3 // \\2\n")
		.gsub(/<\w+.*?>/, "")
		.gsub(/<\/\w+.*?>/, "")
		.gsub(/<!--.*?-->/, "")
		.gsub(/visible anchor\|/, "")
		.gsub(/\{\{(.*?)\}\}/, "\\1")
		.gsub(/\[\[(.*?)\]\]/, "\\1")
		.gsub(/^\s*([\w\- ]+?)\s*\=\s*(0x[0-9a-fA-F]+)\s*\/\/\s*?(.*)$/, "static U \\1 = \\2; //# \\3") 
		.gsub(/^\|\-/, "")
		.gsub(/(\/\/\#)\s+/, "\\1 ")
		.gsub(/^(?<prefix>static\s*U)\s*(?<name>[\w\- \|]+?)(?<postfix>\s*\=)/) { 
			m = $~;
			bitSize = m[:name].match(/^CRC-(\d+)/)[1].to_i
			bitSizeRound2 = [2 ** (Math.log2(bitSize)).ceil(), 8].max;
			m[:prefix] + bitSizeRound2.to_s + " " + m[:name].gsub(/\W/, "_") + m[:postfix] 
		}
	))

	inFile.close()
	outFile.close()
#endif

//# static const U8 CRC_1 = 0x1; //# most hardware; also known as ''parity bit''
static const U8 CRC_3_GSM = 0x3; //# mobile networks{{Cite book|title=ETSI TS 100 
static const U8 CRC_4_ITU = 0x3; //# ITU-T [http://www.itu.int/rec/T-REC-G.704-199810-I/en G.704], p.&nbsp;12
static const U8 CRC_5_EPC = 0x09; //# Radio-frequency identification|Gen 2 RFID{{Cite book|title=Class-1 CRC-5-ITU  = 0x15 //# ITU-T [http://www.itu.int/rec/T-REC-G.704-199810-I/en G.704], p.&nbsp;9
static const U8 CRC_5_USB = 0x05; //# Universal Serial Bus|USB token packets

static const U8 CRC_6_CDMA2000_A = 0x27; //# mobile networksCite book|publisher=3rd Generation Partnership Project 2|date=October 2005|title=Physical layer standard for cdma2000 spread spectrum systems|version=Revision D version 2.0|pages=2–89–2–92|url=http://www.3gpp2.org/public_html/specs/C.S0002-D_v2.0_051006.pdf|access-date=14 October 2013|archive-url=https://web.archive.org/web/20131116065606/http://www.3gpp2.org/public_html/specs/C.S0002-D_v2.0_051006.pdf|archive-date=16 November 2013|url-status=dead

static const U8 CRC_6_CDMA2000_B = 0x07; //# mobile networks

static const U8 CRC_6_DARC = 0x19; //# Data Radio ChannelCite book|title=ETSI EN 300 751|version=V1.2.1|date=January 2003|publisher=European Telecommunications Standards Institute|location=Sophia Antipolis, France|url=http://www.etsi.org/deliver/etsi_en/300700_300799/300751/01.02.01_60/en_300751v010201p.pdf|section=11. Error correction strategy|pages=67–8|access-date=26 January 2016
static const U8 CRC_6_GSM = 0x2F; //# mobile networks
static const U8 CRC_6_ITU = 0x03; //# ITU-T [http://www.itu.int/rec/T-REC-G.704-199810-I/en G.704], p.&nbsp;3
static const U8 CRC_7 = 0x09; //# telecom systems, ITU-T [http://www.itu.int/rec/T-REC-G.707/en G.707], ITU-T 

static const U8 CRC_7_MVB = 0x65; //# Train Communication Network, IEC 60870-5Cite thesis|last=Chakravarty|first=Tridib|others=Philip Koopman, advisor|date=December 2001|title=Performance of Cyclic Redundancy Codes for Embedded Networks|publisher=Carnegie Mellon University|location=Pittsburgh|url=http://www.ece.cmu.edu/~koopman/thesis/chakravarty.pdf|access-date=8 July 2013|pages=5,18
static const U8 CRC_8 = 0xD5; //# DVB-S2Cite book|title=EN 302 307|version=V1.3.1|date=March 2013|publisher=European Telecommunications Standards Institute|location=Sophia Antipolis, France|url=https://www.etsi.org/deliver/etsi_en/302300_302399/302307/01.03.01_60/en_302307v010301p.pdf|section=5.1.4 CRC-8 encoder (for packetized streams only)|page=17|access-date=29 July 2016
static const U8 CRC_8_AUTOSAR = 0x2F; //# automotive integration,Cite book|title=Specification of CRC Routines|version=4.2.2|date=22 July 2015|publisher=AUTOSAR|location=Munich|url=https://www.autosar.org/fileadmin/files/releases/4-2/software-architecture/safety-and-security/standard/AUTOSAR_SWS_CRCLibrary.pdf|section=7.2.1.2 8-bit 0x2F polynomial CRC Calculation|page=24|access-date=24 July 2016|archive-url=https://web.archive.org/web/20160724123829/https://www.autosar.org/fileadmin/files/releases/4-2/software-architecture/safety-and-security/standard/AUTOSAR_SWS_CRCLibrary.pdf|archive-date=24 July 2016|url-status=dead OpenSafetyCite book|title=openSAFETY Safety Profile Specification: EPSG Working Draft Proposal 304|version=1.4.0|date=13 March 2013|publisher=Ethernet POWERLINK Standardisation Group|location=Berlin|url=http://www.ethernet-powerlink.org/en/downloads/technical-documents/action/open-download/download/epsg-wdp-304-v-1-4-0/?no_cache=1|section=5.1.1.8 Cyclic Redundancy Check field (CRC-8 / CRC-16)|page=42|access-date=22 July 2016|archive-url=https://web.archive.org/web/20170812202348/http://www.ethernet-powerlink.org/en/downloads/technical-documents/action/open-download/download/epsg-wdp-304-v-1-4-0/?no_cache=1|archive-date=12 August 2017|url-status=dead

static const U8 CRC_8_Bluetooth = 0xA7; //# wireless connectivityCite book|title=Specification of the Bluetooth System|volume=2|section=B.7.1.1 HEC generation|pages=144–5|publisher=Bluetooth SIG|date=2 December 2014|url=https://www.bluetooth.org/DocMan/handlers/DownloadDoc.ashx?doc_id=286439|access-date=20 October 2014
static const U8 CRC_8_CCITT = 0x07; //# ITU-T [http://www.itu.int/rec/T-REC-I.432.1-199902-I/en I.432.1 (02/99)]; Asynchronous Transfer Mode|ATM Header Error Correction|HEC, ISDN HEC and cell delineation, System_Management_Bus#Packet_Error_Checking|SMBus PEC
static const U8 CRC_8_MaximDallasOneWire = 0x31; //# 1-Wire Bus (computing)|busCite web|author1=Harry Whitfield|url=http://homepages.cs.ncl.ac.uk/harry.whitfield/home.formal/CRCs.html|title=XFCNs for Cyclic Redundancy Check Calculations|archive-url=https://web.archive.org/web/20050525224339/http://homepages.cs.ncl.ac.uk/harry.whitfield/home.formal/CRCs.html|archive-date=25 May 2005|date=24 April 2001

static const U8 CRC_8_DARC = 0x39; //# Data Radio Channel

static const U8 CRC_8_GSM_B = 0x49; //# mobile networks

static const U8 CRC_8_SAE_J1850 = 0x1D; //# AES3; On-board_diagnostics|OBD

static const U8 CRC_8_W_CDMA = 0x9B; //# mobile networksCite book|last=Richardson|first=Andrew|title=WCDMA Handbook|location=Cambridge, UK|publisher=Cambridge University Press|date=17 March 2005|isbn=978-0-521-82815-4|page=223|url=https://books.google.com/books?id=yN5lve5L4vwC&pg=PA223

static const U16 CRC_10 = 0x233; //# ATM; ITU-T [http://www.itu.int/rec/T-REC-I.610/en I.610]

static const U16 CRC_10_CDMA2000 = 0x3D9; //# mobile networks
static const U16 CRC_10_GSM = 0x175; //# mobile networks
static const U16 CRC_11 = 0x385; //# FlexRayCite book|title=FlexRay Protocol Specification|version=3.0.1|publisher=Flexray Consortium|date=October 2010|page=114 (4.2.8 Header CRC (11 bits))
static const U16 CRC_12 = 0x80F; //# telecom systemsCite journal | last = Perez | first = A. | title =  Byte-Wise CRC Calculations | journal = IEEE Micro | volume = 3 | issue = 3 | pages = 40–50 | year = 1983 | doi = 10.1109/MM.1983.291120| s2cid = 206471618 Cite journal | last1 = Ramabadran | first1 =  T.V. | last2 = Gaitonde | first2 = S.S. | title = A tutorial on CRC computations | journal = IEEE Micro | volume = 8 | issue = 4 | year = 1988 | pages = 62–75 | doi = 10.1109/40.7773 | s2cid = 10216862 
static const U16 CRC_12_CDMA2000 = 0xF13; //# mobile networks
static const U16 CRC_12_GSM = 0xD31; //# mobile networks
static const U16 CRC_13_BBC = 0x1CF5; //# Time signal, Radio teleswitch{{Cite web  CRC-14-DARC  = 0x0805 //# Data Radio Channel
static const U16 CRC_14_GSM = 0x202D; //# mobile networks

static const U16 CRC_15_CAN = 0xC599; //# Cite book|date=20 February 2013|institution=Cypress Semiconductor|title=Cyclic Redundancy Check (CRC): PSoC Creator™ Component Datasheet|page=4|url=http://www.cypress.com/file/128066/download|access-date=26 January 2016Cite web|url = http://www.can-cia.org/can-knowledge/can/hash/|title = Cyclic redundancy check (CRC) in CAN frames|access-date = 26 January 2016|website = CAN in Automation

static const U16 CRC_15_MPT1327 = 0x6815; //# Cite book | date=June 1997 |title=A signalling standard for trunked private land mobile radio systems (MPT 1327) |edition=3rd |publisher=Ofcom |section=3.2.3 Encoding and error checking |page=3 |url=http://www.ofcom.org.uk/static const/archive/ra/publication/mpt/mpt_pdf/mpt1327.pdf |access-date=16 July 2012
static const U16 CRC_16_Chakravarty = 0x2F15; //# Optimal for payloads ≤64 bits
static const U16 CRC_16_ARINC = 0xA02B; //# Aircraft Communications Addressing and Reporting System|ACARS applicationsCite journal | url=http://ntl.bts.gov/lib/1000/1200/1290/tn95_66.pdf | title=Air Ground Data Link VHF Airline Communications and Reporting System (ACARS) Preliminary Test Report | date=February 1995 | page=5 | last1=Rehmann | first1=Albert | last2=Mestre | first2=José D. | publisher=Federal Aviation Authority Technical Center | access-date=7 July 2012 | journal= | archive-date=2 August 2012 | archive-url=https://web.archive.org/web/20120802065800/http://ntl.bts.gov/lib/1000/1200/1290/tn95_66.pdf | url-status=dead 
static const U16 CRC_16_CCITT = 0x1021; //# X.25, V.41, HDLC ''FCS'', XMODEM, Bluetooth, PACTOR, Secure Digital card|SD, DigRF, many others; known as ''CRC-CCITT''

static const U16 CRC_16_CDMA2000 = 0xC867; //# mobile networks


static const U16 CRC_16_DIF = 0xC599; //# Cite journal|last=Thaler|first=Pat|title=16-bit CRC polynomial selection|publisher=INCITS T10|date=28 August 2003|url=http://www.t10.org/ftp/t10/document.03/03-290r0.pdf|access-date=11 August 2009

static const U16 CRC_16_DNP3 = 0x3D65; //# DNP, IEC 60870-5|IEC 870, Meter-Bus|M-Bus
static const U16 CRC_16_IBM = 0x8005; //# Binary Synchronous Communications|Bisync, Modbus, Universal Serial Bus|USB, ANSI [https://web.archive.org/web/20091001172850/http://www.incits.org/press/1997/pr97020.htm X3.28], SIA DC-07, many others; also known as ''CRC-16'' and ''CRC-16-ANSI''

static const U16 CRC_16_OpenSafety_A = 0x5935; //# safety fieldbus
static const U16 CRC_16_OpenSafety_B = 0x755B; //# safety fieldbus
static const U16 CRC_16_Profibus = 0x1DCF; //# fieldbus networksCite book|title=PROFIBUS Specification Normative Parts|version=1.0|publisher=Profibus International|date=March 1998|volume=9|section=8.8.4 Check Octet (FCS)|page=906|url=https://www.kuebler.com/PDFs/Feldbus_Multiturn/specification_DP.pdf|access-date=9 July 2016|archive-url=https://web.archive.org/web/20081116195826/http://www.kuebler.com/PDFs/Feldbus_Multiturn/specification_DP.pdf|archive-date=16 November 2008|url-status=dead

static const U32 CRC_17_CAN = 0x1685B; //# CAN FDCite book|title=CAN with Flexible Data-Rate Specification|version=1.0|publisher=Robert Bosch GmbH|date=17 April 2012|page=13|url=http://www.bosch-semiconductors.de/media/pdf_1/canliteratur/can_fd_spec.pdf|url-status=dead|archive-url=https://web.archive.org/web/20130822124728/http://www.bosch-semiconductors.de/media/pdf_1/canliteratur/can_fd_spec.pdf|archive-date=22 August 2013|df=dmy-all (3.2.1 DATA FRAME)
static const U32 CRC_21_CAN = 0x102899; //# CAN FD
static const U32 CRC_24 = 0x5D6DCB; //# FlexRay
static const U32 CRC_24_Radix_64 = 0x864CFB; //# Pretty Good Privacy#OpenPGP|OpenPGP, RTCM104v3
static const U32 CRC_24_WCDMA = 0x800063; //# Used in OS-9|OS-9 RTOS. Residue = 0x800FE3.cite web|url=http://www.roug.org/soren/6809/os9sysprog.html#f.hash|title=OS-9 Operating System System Programmer's Manual|website=www.roug.org

static const U32 CRC_30 = 0x2030B9C7; //# CDMA

static const U32 CRC_32 = 0x04C11DB7; //# ISO 3309 (High-Level Data Link Control|HDLC), ANSI X3.66 (ADCCP), Federal Information Processing Standard|FIPS PUB 71, FED-STD-1003, ITU-T V.42, ISO/IEC/IEEE 802-3 (Ethernet), SATA, MPEG-2, PKZIP, Gzip, Bzip2, POSIX cksum,cite web|url=http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cksum.html|title=cksum|website=pubs.opengroup.org Portable Network Graphics|PNG,Cite web | last1 = Boutell | first1 = Thomas | last2 = Randers-Pehrson | first2 = Glenn  | date = 14 July 1998 | title = PNG (Portable Network Graphics) Specification, Version 1.2 | url = http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html |publisher=Libpng.org | access-date = 3 February 2011 |display-authors=etal ZMODEM, many others

static const U32 CRC_32C = 0x1EDC6F41; //# | iSCSI, SCTP, G.hn payload, SSE4#SSE4.2|SSE4.2, Btrfs, ext4, Ceph (software)|Ceph

static const U32 CRC_32K = 0x741B8CD7; //# | Excellent at Ethernet frame length, poor performance with long files

static const U32 CRC_32K2 = 0x32583499; //# Excellent at Ethernet frame length, poor performance with long files
static const U32 CRC_32Q = 0x814141AB; //# aviation; AIXMCite book|title=AIXM Primer|url=http://www.eurocontrol.int/sites/default/files/service/content/documents/information-management/20060320-aixm-primer.pdf|version=4.5|publisher=European Organisation for the Safety of Air Navigation|date=20 March 2006|access-date=3 Feb 2019

#ifdef UINT64_MAX
static const U64 CRC_40_GSM = 0x0004820009; //# GSM control channel[http://www.etsi.org/deliver/etsi_ts/100900_100999/100909/08.09.00_60/ts_100909v080900p.pdf ETSI TS 100 909] version 8.9.0 (January 2005), Section 4.1.2 aCite book |last=Gammel|first=Berndt M.|date=31 October 2005|title=Matpack documentation: Crypto – Codes  |url=http://www.matpack.de/index.html#DOWNLOAD |publisher=Matpack.de |access-date=21 April 2013 (Note: MpCRC.html is included with the Matpack compressed software source code, under /html/LibDoc/Crypto)Cite journal|last=Geremia|first=Patrick|date=April 1999|title=Cyclic redundancy check computation: an implementation using the TMS320C54x|issue=SPRA530|publisher=Texas Instruments|page=5|url=http://www.ti.com/lit/an/spra530/spra530.pdf|access-date=4 July 2012

static const U64 CRC_64_Ecma = 0x42F0E1EBA9EA3693; //# [http://www.ecma-international.org/publications/standards/Ecma-182.htm ECMA-182]  p.&nbsp;51, XZ Utils
static const U64 CRC_64_ISO = 0x000000000000001B; //# ISO 3309 (High-Level Data Link Control|HDLC), Swiss-Prot/TrEMBL; considered weak for hashingCite journal|last=Jones|first=David T.|title=An Improved 64-bit Cyclic Redundancy Check for Protein Sequences|publisher=University College London|url=http://www.cs.ucl.ac.uk/staff/d.jones/hashnote.pdf|access-date=15 December 2009
#endif

} } } } //# namespace
