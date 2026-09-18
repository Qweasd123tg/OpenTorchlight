
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000001adc38 <CEGUI::FrameComponent::render_impl(CEGUI::Window&, CEGUI::Rect&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0xb08>:
  1adc38:	movss  0x4(%rbx),%xmm1
  1adc3d:	lea    0x110(%rsp),%rdi
  1adc45:	subss  (%rbx),%xmm1
  1adc49:	movss  0x550(%rsp),%xmm6
  1adc52:	movss  0x2c(%rsi),%xmm2
  1adc57:	movss  0x554(%rsp),%xmm3
  1adc60:	addss  %xmm6,%xmm2
  1adc64:	subss  %xmm6,%xmm3
  1adc68:	movss  0xc(%rbx),%xmm4
  1adc6d:	subss  0x8(%rbx),%xmm4
  1adc72:	movss  0x558(%rsp),%xmm5
  1adc7b:	movss  0x28(%rsi),%xmm0
  1adc80:	mov    0x78(%rsp),%rsi
  1adc85:	divss  %xmm1,%xmm2
  1adc89:	addss  %xmm5,%xmm0
  1adc8d:	divss  %xmm1,%xmm3
  1adc91:	movss  0x55c(%rsp),%xmm1
  1adc9a:	subss  %xmm5,%xmm1
  1adc9e:	divss  %xmm4,%xmm0
  1adca2:	addss  %xmm2,%xmm3
  1adca6:	divss  %xmm4,%xmm1
  1adcaa:	addss  %xmm0,%xmm1
  1adcae:	call   c3218 <CEGUI::ColourRect::getSubRectangle(float, float, float, float) const@plt>
