package CodeGenerator;

import java.util.*;
import com.ifx.davex.appjetinteract.App2JetInterface;

public class clk002c_template
{
  protected static String nl;
  public static synchronized clk002c_template create(String lineSeparator)
  {
    nl = lineSeparator;
    clk002c_template result = new clk002c_template();
    nl = null;
    return result;
  }

  public final String NL = nl == null ? (System.getProperties().getProperty("line.separator")) : nl;
  protected final String TEXT_1 = "/*CODE_BLOCK_BEGIN[CLK002.c]*/" + NL + "" + NL + "/*******************************************************************************" + NL + " Copyright (c) 2013, Infineon Technologies AG                                 **" + NL + " All rights reserved.                                                         **" + NL + "                                                                              **" + NL + " Redistribution and use in source and binary forms, with or without           **" + NL + " modification,are permitted provided that the following conditions are met:   **" + NL + "                                                                              **" + NL + " *Redistributions of source code must retain the above copyright notice,      **" + NL + " this list of conditions and the following disclaimer.                        **" + NL + " *Redistributions in binary form must reproduce the above copyright notice,   **" + NL + " this list of conditions and the following disclaimer in the documentation    **" + NL + " and/or other materials provided with the distribution.                       **" + NL + " *Neither the name of the copyright holders nor the names of its contributors **" + NL + " may be used to endorse or promote products derived from this software without** " + NL + " specific prior written permission.                                           **" + NL + "                                                                              **" + NL + " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"  **" + NL + " AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **" + NL + " IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **" + NL + " ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **" + NL + " LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **" + NL + " CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **" + NL + " SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **" + NL + " INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **" + NL + " CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **" + NL + " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **" + NL + " POSSIBILITY OF SUCH DAMAGE.                                                  **" + NL + "                                                                              **" + NL + " To improve the quality of the software, users are encouraged to share        **" + NL + " modifications, enhancements or bug fixes with Infineon Technologies AG       **" + NL + " dave@infineon.com).                                                          **" + NL + "                                                                              **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "**                                                                            **" + NL + "** PLATFORM : Infineon XMC1xxx Series                                         **" + NL + "**                                                                            **" + NL + "** COMPILER : Compiler Independent                                            **" + NL + "**                                                                            **" + NL + "** AUTHOR   : App Developer                                                   **" + NL + "**                                                                            **" + NL + "** MAY BE CHANGED BY USER [Yes/No]: Yes                                       **" + NL + "**                                                                            **" + NL + "** MODIFICATION DATE : Oct 30, 2013                                           **" + NL + "**                                                                            **" + NL + "*******************************************************************************/" + NL + "/* Revision History" + NL + " *****************************************************************************" + NL + " *" + NL + "*/" + NL + "/**" + NL + " * @file   CLK002.c" + NL + " *" + NL + " * @brief  SCU_Clock_CLK002 App" + NL + " *         " + NL + " *  CLK002 App is a singleton app which is used by all applications to configure " + NL + " *  the PLL as well as enable the Clock of Peripheral Units." + NL + " " + NL + " * Revision History" + NL + " * 18 Jan 2013   v1.0.0  Initial Version" + NL + " * 04 Sep 2013   v1.0.4  Added support for XMC1201, XMC1202, XMC1301 devices" + NL + " * 30 Oct 2013   v1.0.6  SystemCoreClockUpdate API called at end of CLK002_Init API" + NL + " */" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Author(s) Identity                                    **" + NL + "********************************************************************************" + NL + "**                                                                            **" + NL + "** Initials     Name                                                          **" + NL + "** ---------------------------------------------------------------------------**" + NL + "** Yogesh       App Developer                                                 **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + " ** INCLUDE FILES                                                             **" + NL + " ******************************************************************************/" + NL + "/** Inclusion of header file */" + NL + "#include <DAVE3.h>" + NL + "" + NL + "/*******************************************************************************" + NL + "**  0                    Private Macro Definitions                             **" + NL + "*******************************************************************************/" + NL + "/* Master Clock setup parameters */  ";
  protected final String TEXT_2 = NL + "#define   CLK002_CLKCR_PCLKSEL           (";
  protected final String TEXT_3 = "U)" + NL + "#define   CLK002_CLKCR_IDIV              (";
  protected final String TEXT_4 = "U)      " + NL + "#define   CLK002_CLKCR_FDIV              (";
  protected final String TEXT_5 = "U)    " + NL + "#define   CLK002_DIRECT_ACCESS_ALLOW     (0xC0U)" + NL + "#define   CLK002_DIRECT_ACCESS_DISALLOW  (0xC3U)" + NL + "" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Private Type Definitions                              **" + NL + "*******************************************************************************/" + NL + "" + NL + "/*******************************************************************************" + NL + "**                 Private Function Declarations:" + NL + "*******************************************************************************/" + NL + "static void     CLK002_lFrequencyUpScaling(void);" + NL + "static void     CLK002_lFrequencyDownScaling(void);" + NL + "static void     CLK002_lDivUpdate(void);" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Extern Declarations                                   **" + NL + "*******************************************************************************/" + NL + "extern void SystemCoreClockUpdate(void);" + NL + "" + NL + "/*******************************************************************************" + NL + "**                      Public Function Definitions                           **" + NL + "*******************************************************************************/" + NL + "/**" + NL + "  * @brief  Function to initialise the Clock Tree based on UI configuration." + NL + "  * @note   -" + NL + "  * @param  None" + NL + "  * @retval None" + NL + "  */" + NL + "void CLK002_Init(void)" + NL + "{" + NL + "    /* Open the lock that protects privileged bits. */" + NL + "    SCU_GENERAL->PASSWD = CLK002_DIRECT_ACCESS_ALLOW;" + NL + "" + NL + "    /* Loop until protection is removed. */" + NL + "    while(((SCU_GENERAL->PASSWD)&SCU_GENERAL_PASSWD_PROTS_Msk))" + NL + "    {" + NL + "\t    ;" + NL + "    }" + NL + "" + NL + "    /* Update PCLK selection mux. */" + NL + "    SCU_CLK->CLKCR|=(((uint32_t)CLK002_CLKCR_PCLKSEL<<\\" + NL + "\t             (uint32_t)SCU_CLK_CLKCR_PCLKSEL_Pos)&SCU_CLK_CLKCR_PCLKSEL_Msk);" + NL + "" + NL + "    CLK002_lDivUpdate();" + NL + "" + NL + "    /*Close the lock opened above. */" + NL + "    SCU_GENERAL->PASSWD = CLK002_DIRECT_ACCESS_DISALLOW;" + NL + "" + NL + "    /* Update the clock variable */" + NL + "    SystemCoreClockUpdate();" + NL + "}" + NL + "" + NL + "/**" + NL + "* @brief  This routine is called by CMSIS startup to find out if clock tree" + NL + "*         setup should be done by it.This routine is WEAKLY defined in CStart." + NL + "*         In the absence of clock app, the weak definition takes precedence" + NL + "*         which always permits clock tree setup by CStart. When clock app is" + NL + "*         defined, this function overrides the CStart definition. Clock tree" + NL + "*         setup is launched and upon completion, control is ceded back to" + NL + "*         CStart.CStart abstains from setting up clock tree and instead" + NL + "*         proceeds with program  loading. Return 0 to disallow CStart from" + NL + "*         performing clock tree setup." + NL + "*/" + NL + "" + NL + "uint32_t AllowClkInitByStartup(void)" + NL + "{" + NL + "    /* Return FALSE - Do not allow any initialisation by startup code. */" + NL + "    return ((uint32_t)0);" + NL + "}" + NL + "/*******************************************************************************" + NL + "**                 Private Function definition:" + NL + "*******************************************************************************/" + NL + "" + NL + "/**" + NL + "  * @brief  Function to update idiv in steps of quard." + NL + "  * @note   -" + NL + "  * @param  None" + NL + "  * @retval None" + NL + "  */" + NL + "static void CLK002_lDivUpdate(void)" + NL + "{" + NL + " /*  Find out current and target value of idiv */" + NL + " uint32_t lCurrIdiv= (uint32_t) 0;      /* Current idiv. */" + NL + " uint32_t lTargetidiv= (uint32_t) 0;    /* Target idiv. */" + NL + " uint32_t lCLKCR;" + NL + " lCurrIdiv = (((SCU_CLK->CLKCR)&SCU_CLK_CLKCR_IDIV_Msk)>>SCU_CLK_CLKCR_IDIV_Pos);" + NL + " lTargetidiv = CLK002_CLKCR_IDIV;" + NL + "" + NL + " /* Update FDIV here, unconditionally. */" + NL + "" + NL + "  lCLKCR = SCU_CLK->CLKCR;" + NL + "  WR_REG(lCLKCR, SCU_CLK_CLKCR_FDIV_Msk, SCU_CLK_CLKCR_FDIV_Pos,CLK002_CLKCR_FDIV);" + NL + "  SCU_CLK->CLKCR = lCLKCR;" + NL + "" + NL + "     /* Delay, till frequency stable, appox. 15us. */" + NL + "" + NL + "" + NL + "  WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);" + NL + "  while (SCU_CLK->CLKCR&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "  {" + NL + "    ;" + NL + "  }" + NL + "" + NL + "" + NL + "    /* Find out current value of direction in which idiv has to update. */" + NL + " if (lCurrIdiv==lTargetidiv)" + NL + "  {" + NL + "   /*No change in IDIV. */" + NL + "  }" + NL + " else if(lCurrIdiv < lTargetidiv)" + NL + "  {" + NL + "    CLK002_lFrequencyDownScaling();" + NL + "  }" + NL + "  else" + NL + "   {" + NL + "     CLK002_lFrequencyUpScaling();" + NL + "   }" + NL + "" + NL + "}" + NL + "" + NL + "/**" + NL + "  * @brief  Function to provide frequency up scaling." + NL + "  * @note   -" + NL + "  * @param  None" + NL + "  * @retval None" + NL + "  */" + NL + "static void     CLK002_lFrequencyUpScaling()" + NL + "{" + NL + "  uint32_t CurrIdiv;" + NL + "  uint32_t TargetIdiv;" + NL + "  uint32_t lCLKCR;" + NL + "  CurrIdiv = (((SCU_CLK->CLKCR)&SCU_CLK_CLKCR_IDIV_Msk)>>SCU_CLK_CLKCR_IDIV_Pos);" + NL + "  TargetIdiv = CLK002_CLKCR_IDIV;" + NL + "  while(1)" + NL + "  {" + NL + "    if(CurrIdiv > (TargetIdiv * 4UL))" + NL + "    {" + NL + "        CurrIdiv = (CurrIdiv & 0xFFFFFFFCU) + 4U;" + NL + "        CurrIdiv  = CurrIdiv >> 2;   /* Divide by 4. */" + NL + "        /* Program interim value of IDIV. */" + NL + "" + NL + "        lCLKCR = SCU_CLK->CLKCR;" + NL + "        WR_REG(lCLKCR, SCU_CLK_CLKCR_IDIV_Msk, SCU_CLK_CLKCR_IDIV_Pos,CurrIdiv);" + NL + "        SCU_CLK->CLKCR = lCLKCR;" + NL + "" + NL + "        /* Wait till frequency stable. */" + NL + "        WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);" + NL + "        while (SCU_CLK->CLKCR&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "        {" + NL + "            ;" + NL + "        }" + NL + "    }" + NL + "    else" + NL + "    {" + NL + "        /* Program TargetIDiv into IDIV bitfield of CLKCR. */" + NL + "        lCLKCR = SCU_CLK->CLKCR;" + NL + "        WR_REG(lCLKCR, SCU_CLK_CLKCR_IDIV_Msk, SCU_CLK_CLKCR_IDIV_Pos,TargetIdiv);" + NL + "        SCU_CLK->CLKCR = lCLKCR;" + NL + "        /* Wait till frequency stable. */" + NL + "        WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);" + NL + "        while (SCU_CLK->CLKCR&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "        {" + NL + "            ;" + NL + "        }" + NL + "        break;" + NL + "    }" + NL + "" + NL + "  }" + NL + "" + NL + "}" + NL + "" + NL + "/**" + NL + "  * @brief  Function to provide frequency up scaling." + NL + "  * @note   -" + NL + "  * @param  None" + NL + "  * @retval None" + NL + "  */" + NL + "static void     CLK002_lFrequencyDownScaling()" + NL + "{" + NL + "    uint32_t CurrIdiv;" + NL + "    uint32_t TargetIdiv;" + NL + "    uint32_t lCLKCR;" + NL + "    CurrIdiv = (((SCU_CLK->CLKCR)&SCU_CLK_CLKCR_IDIV_Msk)>>SCU_CLK_CLKCR_IDIV_Pos);" + NL + "    TargetIdiv = CLK002_CLKCR_IDIV;" + NL + "    while(1)" + NL + "    {" + NL + "        if((CurrIdiv * 4UL) < TargetIdiv )" + NL + "        {" + NL + "            CurrIdiv  = CurrIdiv << 2;   /* Multiply by 4. */" + NL + "            /* Program interim value of IDIV */" + NL + "            lCLKCR = SCU_CLK->CLKCR;" + NL + "            WR_REG(lCLKCR, SCU_CLK_CLKCR_IDIV_Msk, SCU_CLK_CLKCR_IDIV_Pos,CurrIdiv);" + NL + "            SCU_CLK->CLKCR = lCLKCR;" + NL + "            /* Wait till frequency stable. */" + NL + "            WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);" + NL + "            while (SCU_CLK->CLKCR&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "            {" + NL + "                ;" + NL + "            }" + NL + "        }" + NL + "        else" + NL + "        {" + NL + "            /* Program TargetIDiv into IDIV bitfield of CLKCR */" + NL + "            lCLKCR = SCU_CLK->CLKCR;" + NL + "            WR_REG(lCLKCR, SCU_CLK_CLKCR_IDIV_Msk, SCU_CLK_CLKCR_IDIV_Pos,TargetIdiv);" + NL + "            SCU_CLK->CLKCR = lCLKCR;" + NL + "            /* Wait till frequency stable. */" + NL + "           " + NL + "            WR_REG(SCU_CLK->CLKCR, SCU_CLK_CLKCR_CNTADJ_Msk, SCU_CLK_CLKCR_CNTADJ_Pos,CLK002_DELAYCNT);" + NL + "            while (SCU_CLK->CLKCR&(SCU_CLK_CLKCR_VDDC2LOW_Msk))" + NL + "            {" + NL + "                ;" + NL + "            }" + NL + "             break;" + NL + "        }" + NL + "" + NL + "\t  }" + NL + "}" + NL + "" + NL + "/*CODE_BLOCK_END*/";
  protected final String TEXT_6 = NL;

  public String generate(Object argument)
  {
    final StringBuffer stringBuffer = new StringBuffer();
     App2JetInterface app = (App2JetInterface) argument; 
     String AppBaseuri = "app/clk002/0";
     String MappedUri = null; 
    stringBuffer.append(TEXT_1);
    int pclksel = app.getIntegerValue(AppBaseuri + "/clk_uri/clkcr/pclksel");
    int idiv = app.getIntegerValue(AppBaseuri + "/clk_uri/clkcr/idiv");
    int fdiv =app.getIntegerValue(AppBaseuri + "/clk_uri/clkcr/fdiv");
    stringBuffer.append(TEXT_2);
    stringBuffer.append(pclksel);
    stringBuffer.append(TEXT_3);
    stringBuffer.append(idiv);
    stringBuffer.append(TEXT_4);
    stringBuffer.append(fdiv);
    stringBuffer.append(TEXT_5);
    stringBuffer.append(TEXT_6);
    return stringBuffer.toString();
  }
}
