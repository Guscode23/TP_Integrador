package com.proyecto.carrito.Security;

import java.util.Collection;
import java.util.Collections;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import com.proyecto.carrito.model.Cliente;



public class UserDetailsImpl implements UserDetails {

	
	private final Cliente cliente = new Cliente();
	
	
	public UserDetailsImpl(Cliente cliente2) {
		// TODO Auto-generated constructor stub
	}

	@Override
	public Collection<? extends GrantedAuthority> getAuthorities() {
		// TODO Auto-generated method stub
		return Collections.emptyList();
	}

	@Override
	public String getPassword() {
		// TODO Auto-generated method stub
		return cliente.getPassword();
	}

	@Override
	public String getUsername() {
		// TODO Auto-generated method stub
		return cliente.getEmail();
	}

	@Override
	public boolean isAccountNonExpired() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean isAccountNonLocked() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean isCredentialsNonExpired() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean isEnabled() {
		// TODO Auto-generated method stub
		return false;
	}
	
	public String getNombre() {
		return cliente.getNombre();
	}

	
	
	
	
	
	
}
