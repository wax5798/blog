/*************************************************************************
	> File Name: pcap_parser.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月24日 星期六 20时25分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct pcap_file_header {
	uint32_t magic;			// 为 0xa1b2c3d4 或者 0xd4c3b2a1，用来识别字节顺序，前者为大端模式，后者为小端模式
	uint16_t version_major; // 主版本号，一般为 0x0200
	uint16_t version_minor; // 次版本号，一般为 0x0400
	uint32_t thiszone;		// GMT 和本地时间的差值，单位秒。一般为零
	uint32_t sigfigs;		// 时间戳的精度，一般为全零
	uint32_t snaplen;		// 设置所抓获的数据包的最大长度，如果所有数据包都要抓获，将该值设置为65535
	uint32_t linktype;		// 链路类型
};
/* 链路类型对应关系如下
   0				BSD loopback devices, except for later OpenBSD
   1              	Ethernet, and Linux loopback devices
   6              	802.5  Token Ring
   7              	ARCnet
   8              	SLIP
   9				PPP
   10				FDDI
   100				LLC/SNAP-encapsulated  ATM 
   101				"raw IP", with no link
   102				BSD/OS  SLIP
   103             	BSD/OS  PPP
   104             	Cisco  HDLC
   105             	802.11
   108             	later OpenBSD loopback devices (with the AF_value in network byte order)
   113             	special  Linux  "cooked"  capture
   114             	LocalTalk
   */

struct pcap_pkt_header {
	uint32_t ts_s;			// 时间戳高位，精确到秒，从 GMT 开始记
	uint32_t ts_ms;			// 时间戳低位，精确到毫秒
	uint32_t caplen;		// 抓获到数据帧的长度
	uint32_t len;			// 离线数据长度，网路中实际数据帧的长度，一般不大于Caplen，多数情况下和Caplen值一样
};

int main(int argc, char *argv[])
{
	int fd = -1;
	struct pcap_file_header fhdr = {0};
	struct pcap_pkt_header phdr = {0};
	uint8_t databuf[2048] = {0};
	int datalen = 0;

	if (2 != argc)
	{
		printf("usage: %s pcap_file_name\n", argv[0]);
		return 0;
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		printf("open %s failed: %s\n", argv[1], strerror(errno));
		goto leave;
	}

	if (sizeof(fhdr) != read(fd, &fhdr, sizeof(fhdr)))
	{
		printf("read file failed: %s\n", strerror(errno));
		goto leave;
	}

	printf("file header info: magic(0x%08x), major_version(0x%04x), minor_version(0x%04x), thiszone(0x%08x), sigfigs(0x%08x), snaplen(0x%08x), linktype(0x%08x)\n", fhdr.magic, fhdr.version_major, fhdr.version_minor, fhdr.thiszone, fhdr.sigfigs, fhdr.snaplen, fhdr.linktype);

	while (sizeof(phdr) == read(fd, &phdr, sizeof(phdr)))
	{
		int i = 0;

		datalen = read(fd, databuf, phdr.caplen);
		if (phdr.caplen != datalen)
		{
			printf("read data len err(%d - %d): %s\n", phdr.caplen, datalen, strerror(errno));
			break;
		}

		printf("packet header info: ts_s(%d), ts_ms(%d), caplen(%d), len(%d):", phdr.ts_s, phdr.ts_ms, phdr.caplen, phdr.len);

		for (i = 0; i < phdr.caplen; i ++)
		{
			if (0 == i % 16) printf("\n");
			else if (0 == i % 8) printf(" ");

			printf("%02x ", databuf[i]);
		}
		printf("\n");
	}

leave:
	if (fd >= 0) close(fd);

	return 0;
}
