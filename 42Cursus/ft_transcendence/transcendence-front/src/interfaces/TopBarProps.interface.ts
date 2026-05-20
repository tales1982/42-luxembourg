export interface TopBarProps {
  onMenuToggle: () => void;
  searchValue: string;
  onSearchChange: (value: string) => void;
}