return {
  {
    "NvChad/nvim-colorizer.lua",
    config = function()
      require("colorizer").setup()
    end,
  },

  {
    "ziontee113/color-picker.nvim",
    config = function()
      require("color-picker").setup()
    end,
  },
}
